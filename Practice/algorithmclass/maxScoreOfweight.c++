#include <stdio.h>
#include <stdlib.h>

int sum(int a, int b, int *weight)
{
    int sum = 0;
    for (int i = a; i <= b; i++)
        sum = sum + weight[i];
    return sum;
}

int main()
{
    int weight[4] = {4, 4, 5, 9};
    int m[5][5];                //最大得分
    int s[5][5];                //最大得分时对应的k值

    for (int i = 1; i < 5; i++) 
    {
        for (int j = 1; j < 5; j++)
        {
            m[i][j] = 0;
        }
    }

    for (int x = 1; x < 4; x++)
    {
        for (int i = 1, j = x + 1; j < 5; i++, j++)
        {
            for (int k = i; k < j; k++) //遍历k值
            {
                int x = m[i][k] + m[k + 1][j] + sum(i - 1, j - 1, weight);
                if (x > m[i][j])
                {
                    m[i][j] = x;
                    s[i][j] = k;
                }
            }
        }
    }

    printf("最大得分：%d\n", m[1][4]);

    system("pause");
    return 0;
}
