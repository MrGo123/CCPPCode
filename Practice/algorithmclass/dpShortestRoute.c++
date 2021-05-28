#include <iostream>
#define NODE_NUM 10
#define MAX_COST 100
using namespace std;

int main()
{

    // 邻接矩阵构造图
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

    // 每一个节点最短路径中的前驱节点
    int preNode[NODE_NUM];

    // 每一个节点的最短路消耗
    int perNodeShortestCost[NODE_NUM];

    for (int i = 0; i < NODE_NUM; i++)
    {
        preNode[i] = -1;
        perNodeShortestCost[i] = MAX_COST;
    }

    //1号节点
    preNode[0] = 0;
    perNodeShortestCost[0] = 0;

    // 从2号节点开始
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

    //打印每一个节点的最短路及其前一个节点
    cout << "Node"
         << " preNode"
         << " "
         << " mincost" << endl;
         
    for (int i = 0; i < NODE_NUM; i++)
    {
        cout << i + 1 << "       " << preNode[i] + 1 << "      " << perNodeShortestCost[i] << endl;
    }

    //10号节点
    cout << "10号节点的最短路径为：" << perNodeShortestCost[9] << endl;
    cout << "它的路径是：10";

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