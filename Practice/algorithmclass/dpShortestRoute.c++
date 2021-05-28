#include <iostream>
#define NODE_NUM 10
#define MAX_COST 100
using namespace std;

int main()
{

    // �ڽӾ�����ͼ
    int graph[NODE_NUM][NODE_NUM] = {
        {0, 4, 2, 3, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 10, 9, 0, 0, 0, 0},
        {0, 0, 0, 0, 6, 7, 10, 0, 0, 0},
        {0, 0, 0, 0, 0, 3, 8, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 4, 8, 0},
        {0, 0, 0, 0, 0, 0, 0, 9, 6, 0},
        {0, 0, 0, 0, 0, 0, 0, 5, 4, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 8},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    // ÿһ���ڵ����·���е�ǰ���ڵ�
    int preNode[NODE_NUM];

    // ÿһ���ڵ�����·����
    int perNodeShortestCost[NODE_NUM];

    for (int i = 0; i < NODE_NUM; i++)
    {
        preNode[i] = -1;
        perNodeShortestCost[i] = MAX_COST;
    }

    //1�Žڵ�
    preNode[0] = 0;
    perNodeShortestCost[0] = 0;

    // ��2�Žڵ㿪ʼ
    for (int i = 1; i < NODE_NUM; i++)
    {
        for (int j = 0; j < NODE_NUM; j++)
        {
            if (graph[j][i] == 0)
                continue;

            int currCost = graph[j][i] + perNodeShortestCost[j];

            if (currCost < perNodeShortestCost[i])
            {
                preNode[i] = j;
                perNodeShortestCost[i] = currCost;
            }
        }
    }

    //��ӡÿһ���ڵ�����·����ǰһ���ڵ�
    cout << "Node"
         << " preNode"
         << " "
         << " mincost" << endl;
         
    for (int i = 0; i < NODE_NUM; i++)
    {
        cout << i + 1 << "       " << preNode[i] + 1 << "      " << perNodeShortestCost[i] << endl;
    }

    //10�Žڵ�
    cout << "10�Žڵ�����·��Ϊ��" << perNodeShortestCost[9] << endl;
    cout << "����·���ǣ�10";

    int i = 9;
    while (preNode[i])
    {
        cout << "<-" << preNode[i] + 1;
        i = preNode[i];
    }

    cout << "<-" << preNode[0] + 1;
    cout << endl;

    system("pause");
    return 0;
}