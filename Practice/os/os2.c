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

void print(struct storagellink *total, struct storagellink *already) //���
{
	struct storagellink *p, *q;
	printf("\nδ����ռ�\n");
	for (p = total; p != NULL; p = p->next)
	{
		printf("���:%4d;����:%4d\n", p->seq, p->len);
	}
	printf("\n�ѷ���ռ�\n");
	for (q = already; q != NULL; q = q->next)
	{
		printf("���:%4d;����:%4d\n", q->seq, q->len);
	}
	printf("\n");
}

struct list *distribution(struct storagellink *total, struct storagellink *already, int need) //�����ڴ�
{
	int flag = 0;
	struct storagellink *p, *q, *cut, *del; //cut����δ��������õĿռ�
	struct list *back;						//�����ѷ����δ�����ڴ�ͷָ��
	int size = sizeof(struct list);
	back = (struct list *)malloc(size);
	size = sizeof(struct storagellink);

	for (p = total; p != NULL; p = p->next) //��δ��������Ѱ���Ƿ��������Ҫ��Ŀռ�
	{
		if (p->len >= need) //�ҵ�
		{
			cut = (struct storagellink *)malloc(size); //���ÿռ��иʹ��cut�洢�и�ռ���źͳ���
			cut->seq = p->seq;
			cut->len = need;
			cut->next = NULL;
			p->seq += need; //��ű仯
			p->len -= need;//�ռ����
			//�����δ��������ĵ�һ���ڵ㣬������ڵ�պñ��ָ�=0�������δ��������ͷ
			del = total;
			if (del->len == 0)
			{
				total = del->next;
			}
			else//�ռ���ʣ��ɾ������֮��Ϊ0�Ľڵ㣬�����ȸոպ�
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
			//�ѷ����
			if (already == NULL) //����ѷ���ռ�Ϊ��
			{
				already = cut;
			}
			else
			{
				for (q = already; q != NULL; q = q->next) //Ѱ��cut���ѷ������в����
				{
					if (q == already && cut->seq < q->seq) //�����Ϊ��һ�����ѷ��������ͷ��Ϊ��һ���ڵ�cut
					{
						cut->next = q;
						already = cut;
						break;
					}
					else if (q->seq < cut->seq && q->next == NULL) //�����Ϊ���һ�������ӵ���β
					{
						q->next = cut;
						cut->next = NULL;
						break;
					}
					else if (q->next->seq > cut->seq) //��һ�ڵ���ڲ���㣬���뵽�м�
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
		printf("\n>�޷�����ռ������\n");
	}
	else
	{
		printf("\n>���̿ռ��ѷ���\n");
	}
	getch();
	back->start = total;
	back->end = already;
	return back;
}

struct list *recycling(struct storagellink *total, struct storagellink *already, int rec) //�����ڴ�
{
	int flag = 0, i;
	struct storagellink *p, *q, *pro;
	struct list *back;
	p = total;
	q = already;
	int size = sizeof(struct list);
	back = (struct list *)malloc(size);
	// �һ��սڵ㣬�ҵ�flag=1������flag=0
	if (already != NULL) //�ѷ������н���
	{
		if (q->seq == rec) //���սڵ�Ϊ��һ�ڵ�
		{
			flag = 1;
			pro = q;
			already = already->next;
			pro->next = NULL;
		}
		while (q->next != NULL) //���սڵ�Ϊ�����ڵ㣬�Ǿ��ҵ�����ڵ�
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
		printf("\n>δ�ҵ�Ҫ���ս������\n");
		getch();
	}
	else//�ҵ���flag=1
	{
		for (i = 0; p != NULL; p = p->next, ++i) //Ѱ�һ�������ԭδ������֮��Ĺ�ϵ
		{
			if (pro->seq < p->seq && pro->seq + pro->len < p->seq && i == 0) //���սڵ�Ϊ��ͷ����ԭδ������������
			{
				pro->next = p;
				total = pro;
				break;
			}
			else if (pro->seq < p->seq && pro->seq + pro->len == p->seq && i == 0) //���սڵ�Ϊ��ͷ����ԭδ������������
			{
				pro->next = p->next;
				pro->len += p->len;
				total = pro;
				break;
			}
			else if (p->seq < pro->seq && p->next == NULL && p->seq + p->len == pro->seq) //�������������λ�ã���ԭδ������������
			{
				p->len += pro->len;
				break;
			}
			else if (p->seq < pro->seq && p->next == NULL && p->seq + p->len < pro->seq) //�������������λ�ã���ԭδ������������
			{
				p->next = pro;
				pro->next = NULL;
				break;
			}
			else if (pro->seq > p->seq && p->seq + p->len == pro->seq && pro->seq < p->next->seq && pro->seq + pro->len < p->next->seq) //������������δ����䣬��ǰһδ������������
			{
				p->len += pro->len;
				break;
			}
			else if (pro->seq > p->seq && p->seq + p->len < pro->seq && pro->seq < p->next->seq && pro->seq + pro->len < p->next->seq) //������������δ����䣬������δ������������
			{
				pro->next = p->next;
				p->next = pro;
				break;
			}
			else if (pro->seq > p->seq && p->seq + p->len < pro->seq && pro->seq < p->next->seq && pro->seq + pro->len == p->next->seq) //������������δ����䣬���һδ������������
			{
				pro->len += p->next->len;
				pro->next = p->next->next;
				p->next = pro;
				break;
			}
			else if (pro->seq > p->seq && p->seq + p->len == pro->seq && pro->seq < p->next->seq && pro->seq + pro->len == p->next->seq) //������������δ����䣬������δ������������
			{
				p->len += pro->len + p->next->len;
				p->next = p->next->next;
				break;
			}
		}
		if (p == NULL) //δ������Ϊ��
		{
			total = pro;
		}
		printf("\n>�����ѻ���\n");
		getch();
	}
	back->start = total;
	back->end = already;
	return back; //����������������ָ��
}

int main(int argc, char const *argv[])
{
	int flag = 1, len;
	struct storagellink *total, *already;
	struct list *back;
	int size = sizeof(struct storagellink);
	total = (struct storagellink *)malloc(size);
	already = (struct storagellink *)malloc(size);
	printf("\t�洢����-�ɱ����\n");
	printf("�����ڴ�ռ��С��");
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
		printf("\t�洢����-�ɱ����\n");
		printf("�ڴ�ռ��С��%d", len);
		printf("\n----------------------------------------------------\n");
		print(total, already);
		printf("----------------------------------------------------\n");
		printf("��ѡ��Ҫ���ڴ�Ĳ���\n[1] ��������\t[2] ���ս���\t[3] �˳�����\n\n>>>");
		scanf("%s", &operation);
		//getchar();
		if (operation == '1') //����ѡ��
		{
			printf("\n�������������Ŀռ�:");
			scanf("%d", &need);
			if (need > 0)
			{
				back = distribution(total, already, need);
				total = back->start;
				already = back->end;
			}
			else
			{
				printf("\n>��������\n");
				getch();
			}
		}
		else if (operation == '2') //����ѡ��
		{
			printf("\n������Ҫ���յĿռ����:");
			scanf("%d", &rec);
			back = recycling(total, already, rec);
			total = back->start;
			already = back->end;
		}
		else if (operation == '3')
		{
			printf("\n>���˳�\n");
			flag = 0;
			getch();
		}
		else
		{
			printf("\n>ָ����Ч\n");
			getch();
		}
	}
	system("pause");
	return 0;
}