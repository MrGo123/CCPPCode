#include <stdio.h>
#include <stdlib.h>

int max(int a, int b)
{
    return a >= b ? a : b;
}
int main()
{

    int num = 5;
    int m = 15;
    int left = m;
    int w[6] = {0, 3, 4, 7, 8, 9};
    int v[6] = {0, 4, 5, 10, 11, 13};

    int dp[6][16] = {{0}};

    for (int i = 1; i <6; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (j < w[i])
            {
                dp[i][j] = dp[i - 1][j];
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i]] + v[i]);
            }
        }
    }
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            printf("%d ", dp[i][j]);
        }
        printf("\n");
    }

    system("pause");
    return 0;
}


