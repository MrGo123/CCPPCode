#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

struct storagellink
{
	int seq;
	int len;
	struct storagellink *next;
};

struct list
{
	struct storagellink *start;
	struct storagellink *end;
};

void print(struct storagellink *total, struct storagellink *already) //输出
{
	struct storagellink *p, *q;
	printf("\n未分配空间\n");
	for (p = total; p != NULL; p = p->next)
	{
		printf("序号:%4d;长度:%4d\n", p->seq, p->len);
	}
	printf("\n已分配空间\n");
	for (q = already; q != NULL; q = q->next)
	{
		printf("序号:%4d;长度:%4d\n", q->seq, q->len);
	}
	printf("\n");
}

struct list *distribution(struct storagellink *total, struct storagellink *already, int need) //分配内存
{
	int flag = 0;
	struct storagellink *p, *q, *cut, *del; //cut：从未分配区获得的空间
	struct list *back;						//返回已分配和未分配内存头指针
	int size = sizeof(struct list);
	back = (struct list *)malloc(size);
	size = sizeof(struct storagellink);

	for (p = total; p != NULL; p = p->next) //从未分配区表寻找是否存在满足要求的空间
	{
		if (p->len >= need) //找到
		{
			cut = (struct storagellink *)malloc(size); //将该空间切割，使用cut存储切割空间序号和长度
			cut->seq = p->seq;
			cut->len = need;
			cut->next = NULL;
			p->seq += need; //序号变化
			p->len -= need;//空间减少
			//如果是未分配区表的第一个节点，且这个节点刚好被分割=0，则更新未分配区表头
			del = total;
			if (del->len == 0)
			{
				total = del->next;
			}
			else//空间有剩，删除分配之后为0的节点，即长度刚刚好
			{
				while (del->next != NULL)
				{
					if (del->next->len == 0)
					{
						del->next = del->next->next;
						break;
					}
					del = del->next;
				}
			}
			//已分配表
			if (already == NULL) //如果已分配空间为无
			{
				already = cut;
			}
			else
			{
				for (q = already; q != NULL; q = q->next) //寻找cut在已分配区中插入点
				{
					if (q == already && cut->seq < q->seq) //插入点为第一个，已分配区表表头变为第一个节点cut
					{
						cut->next = q;
						already = cut;
						break;
					}
					else if (q->seq < cut->seq && q->next == NULL) //插入点为最后一个，链接到表尾
					{
						q->next = cut;
						cut->next = NULL;
						break;
					}
					else if (q->next->seq > cut->seq) //下一节点大于插入点，插入到中间
					{
						cut->next = q->next;
						q->next = cut;
						break;
					}
				}
			}
			flag = 1;
		}
	}
	if (flag == 0)
	{
		printf("\n>无法分配空间给进程\n");
	}
	else
	{
		printf("\n>进程空间已分配\n");
	}
	getch();
	back->start = total;
	back->end = already;
	return back;
}

struct list *recycling(struct storagellink *total, struct storagellink *already, int rec) //回收内存
{
	int flag = 0, i;
	struct storagellink *p, *q, *pro;
	struct list *back;
	p = total;
	q = already;
	int size = sizeof(struct list);
	back = (struct list *)malloc(size);
	// 找回收节点，找到flag=1，否则flag=0
	if (already != NULL) //已分配区有进程
	{
		if (q->seq == rec) //回收节点为第一节点
		{
			flag = 1;
			pro = q;
			already = already->next;
			pro->next = NULL;
		}
		while (q->next != NULL) //回收节点为其他节点，那就找到这个节点
		{
			if (q->next->seq == rec)
			{
				flag = 1;
				pro = q->next;
				q->next = q->next->next;
				pro->next = NULL;
				break;
			}
			q = q->next;
		}
	}
	if (flag == 0)
	{
		printf("\n>未找到要回收进程序号\n");
		getch();
	}
	else//找到，flag=1
	{
		for (i = 0; p != NULL; p = p->next, ++i) //寻找回收区与原未分配区之间的关系
		{
			if (pro->seq < p->seq && pro->seq + pro->len < p->seq && i == 0) //回收节点为开头，与原未分配区无连接
			{
				pro->next = p;
				total = pro;
				break;
			}
			else if (pro->seq < p->seq && pro->seq + pro->len == p->seq && i == 0) //回收节点为开头，与原未分配区有连接
			{
				pro->next = p->next;
				pro->len += p->len;
				total = pro;
				break;
			}
			else if (p->seq < pro->seq && p->next == NULL && p->seq + p->len == pro->seq) //回收区处于最后位置，与原未分配区有连接
			{
				p->len += pro->len;
				break;
			}
			else if (p->seq < pro->seq && p->next == NULL && p->seq + p->len < pro->seq) //回收区处于最后位置，与原未分配区无连接
			{
				p->next = pro;
				pro->next = NULL;
				break;
			}
			else if (pro->seq > p->seq && p->seq + p->len == pro->seq && pro->seq < p->next->seq && pro->seq + pro->len < p->next->seq) //回收区在两个未分配间，与前一未分配区有连接
			{
				p->len += pro->len;
				break;
			}
			else if (pro->seq > p->seq && p->seq + p->len < pro->seq && pro->seq < p->next->seq && pro->seq + pro->len < p->next->seq) //回收区在两个未分配间，与两个未分配区无连接
			{
				pro->next = p->next;
				p->next = pro;
				break;
			}
			else if (pro->seq > p->seq && p->seq + p->len < pro->seq && pro->seq < p->next->seq && pro->seq + pro->len == p->next->seq) //回收区在两个未分配间，与后一未分配区有连接
			{
				pro->len += p->next->len;
				pro->next = p->next->next;
				p->next = pro;
				break;
			}
			else if (pro->seq > p->seq && p->seq + p->len == pro->seq && pro->seq < p->next->seq && pro->seq + pro->len == p->next->seq) //回收区在两个未分配间，与两个未分配区有连接
			{
				p->len += pro->len + p->next->len;
				p->next = p->next->next;
				break;
			}
		}
		if (p == NULL) //未分配区为无
		{
			total = pro;
		}
		printf("\n>进程已回收\n");
		getch();
	}
	back->start = total;
	back->end = already;
	return back; //返回两个分配区的指针
}

int main(int argc, char const *argv[])
{
	int flag = 1, len;
	struct storagellink *total, *already;
	struct list *back;
	int size = sizeof(struct storagellink);
	total = (struct storagellink *)malloc(size);
	already = (struct storagellink *)malloc(size);
	printf("\t存储管理-可变分区\n");
	printf("输入内存空间大小：");
	scanf("%d", &total->len);
	len = total->len;
	total->seq = 0;
	total->next = NULL;
	already = NULL;
	while (flag)
	{
		char operation;
		int need, rec;
		system("cls");
		printf("\t存储管理-可变分区\n");
		printf("内存空间大小：%d", len);
		printf("\n----------------------------------------------------\n");
		print(total, already);
		printf("----------------------------------------------------\n");
		printf("请选择要对内存的操作\n[1] 创建进程\t[2] 回收进程\t[3] 退出管理\n\n>>>");
		scanf("%s", &operation);
		//getchar();
		if (operation == '1') //分配选项
		{
			printf("\n请输入进程所需的空间:");
			scanf("%d", &need);
			if (need > 0)
			{
				back = distribution(total, already, need);
				total = back->start;
				already = back->end;
			}
			else
			{
				printf("\n>输入有误\n");
				getch();
			}
		}
		else if (operation == '2') //回收选项
		{
			printf("\n请输入要回收的空间序号:");
			scanf("%d", &rec);
			back = recycling(total, already, rec);
			total = back->start;
			already = back->end;
		}
		else if (operation == '3')
		{
			printf("\n>已退出\n");
			flag = 0;
			getch();
		}
		else
		{
			printf("\n>指令无效\n");
			getch();
		}
	}
	system("pause");
	return 0;
}