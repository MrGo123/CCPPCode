/*
本关任务：给定N个物品和一个背包，背包的容量为W， 假设背包容量范围在[0，15]，
第i个物品对应的体积和价值分别为W[i]和v[i]。各种物品的价值和重量如下：
     物品编号   1   2   3   4   5
      重量W    3   4   7   8   9
      价值V    4   5   10  11  13
求: 如何选择装入背包的物品，使得装入背包的物品的总价值为最大。

*/
#include <stdio.h>
#include <stdlib.h>

int max(int a, int b)
{
    return a >= b ? a : b;
}

int main(void)
{
    int w[6] = {0};        //物品重量
    int v[6] = {0};        //物品价值
    int bagV = 15;         //背包容量
    int dp[6][16] = {{0}}; //dp表格
    int num = 5;
    for (int i = 1; i < 6; i++)
    {
        scanf("%d", &w[i]);
        scanf("%d", &v[i]);
    }
//动态规划计算
    for (int i = 1; i <= 5; i++)
    {
        for (int j = 1; j <= bagV; j++)
        {
            if (j < w[i])
                dp[i][j] = dp[i - 1][j];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i]] + v[i]);
        }
    }
    printf("w v ");
    for (int i = 0; i < 16; i++)
    {
        printf("%d",i);
        if(i<15){
            printf(" ");
        }
    }
    printf("\n");
    //dp表输出
    for (int i = 0; i < 6; i++)
    {
        printf("%d ",w[i]);
        printf("%d ",v[i]);
        for (int j = 0; j < 16; j++)
        {
            printf("%d", dp[i][j]);
            if(j<15){
                printf(" ");
            }
        }
        printf("\n");
    }

    system("pause");
    return 0;
}
