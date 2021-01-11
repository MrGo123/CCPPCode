#include <stdio.h>
#include <stdlib.h>
#define MAX_COUNT 10000

int m[7][7]; //
int s[7][7]; //矩阵连乘最少次数时的k值


void printResult(int i, int j) 
{
    if (i == j)
    {
        printf("A%d", i);
        return;
    }
    printf("(");
    printResult(i, s[i][j]); //k值以前
    printf("*");
    printResult(s[i][j] + 1, j); //k值以后
    printf(")");
}

int main()
{
    int matrix[7] = {5, 10, 3, 12, 5, 50, 6};
    // 结果数组初始化
    for (int i = 1; i <7; i++)
    {
        for (int j = 1; j <7; j++)
        {
            m[i][j] = MAX_COUNT;//令每个计算次数都最大
        }
        m[i][i] = 0;
    }

    //求m[i][j]
    for (int x = 1; x < 6; x++) 
    {
        for (int i = 1, j = x + 1; j <7; i++, j++)
        {
            for (int k = i; k < j; k++) //遍历k值
            {
                int x = m[i][k] + m[k + 1][j] + matrix[i - 1] * matrix[k] * matrix[j];
                if (x < m[i][j])
                {
                    m[i][j] = x;
                    s[i][j] = k;
                }
            }
        }
    }
    
    printf("最佳连乘次序：");
    printResult(1, 6);

    printf("\n最少乘法次数：%d\n", m[1][6]);

    system("pause");
    return 0;
}
