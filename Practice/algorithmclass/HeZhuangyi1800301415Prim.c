#include <stdio.h>
#include <stdlib.h>

#define MAX_L 100 //假设所有的边权值都小于100

//邻接矩阵表示图，0~5=A~F
int graph[6][6] = {
    {0, 5, 6, 4, 0, 0},
    {5, 0, 1, 2, 0, 0},
    {6, 1, 0, 2, 5, 3},
    {4, 2, 2, 0, 0, 4},
    {0, 0, 5, 0, 0, 4},
    {0, 0, 3, 4, 4, 0}};

int selected[6] = {-1};           //存选择了的节点
int left[6] = {0, 1, 2, 3, 4, 5}; //存未选择的节点

//判断某一点是否在待选择集合中
int isInLeft(int n)
{
    for (int i = 0; i < 6; i++)
    {
        if (left[i] == n)
        {
            return 1;
        }
    }
    return 0;
}
//判断某一点是否在已选择集合中
int isNotInSelected(int n)
{
    for (int i = 0; i < 6; i++)
    {
        if (selected[i] == n)
        {
            return 0;
        }
    }
    return 1;
}
//从Selected内的所有边找最小的边对应的节点，且节点不存在Selected中
int getNextNode()
{
    int min = MAX_L;
    int index = -1;

    for (int i = 0; i < 6 && selected[i] != -1; i++) //从已选择的集合中取点
    {
        for (int j = 0; j < 6; j++) //从当前点找最小
        {
            if (graph[selected[i]][j] < min && graph[selected[i]][j] != 0 && isInLeft(j) && isNotInSelected(j)) //先判是不是最小且不为0，再判这个节点是不是在待查找中
            {
                min = graph[selected[i]][j];
                index = j;
            }
        }
    }

    return index;
}

int main()
{

    selected[0] = 0; //从第0个节点开始，即A。
    left[0] = -1;    //0号点已取

    //将已经访问的节点记录
    for (int i = 1; i < 6; i++)
    {
        int nodeIndex = getNextNode();
        selected[i] = nodeIndex; //把对应的节点放到已取节点的集合中
        left[nodeIndex] = -1;    //把已经访问的节点删除
    }

    //打印结果，按顺序打印Selected数组内容，每一个数组对应字母
    for (int i = 0; i < 6; i++)
    {
        switch (selected[i])
        {
        case 0:
            printf("A");
            break;
        case 1:
            printf("B");
            break;
        case 2:
            printf("C");
            break;
        case 3:
            printf("D");
            break;
        case 4:
            printf("E");
            break;
        case 5:
            printf("F");
            break;
        default:
            break;
        }
        if (i<5)
        {
            printf("-");
        }
        
    }
    system("pause");
    return 0;
}
