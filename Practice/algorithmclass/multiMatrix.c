#include <stdio.h>
#include <stdlib.h>
#define MAX_COUNT 10000

int m[7][7]; //
int s[7][7]; //�����������ٴ���ʱ��kֵ


void printResult(int i, int j) 
{
    if (i == j)
    {
        printf("A%d", i);
        return;
    }
    printf("(");
    printResult(i, s[i][j]); //kֵ��ǰ
    printf("*");
    printResult(s[i][j] + 1, j); //kֵ�Ժ�
    printf(")");
}

int main()
{
    int matrix[7] = {5, 10, 3, 12, 5, 50, 6};
    // ��������ʼ��
    for (int i = 1; i <7; i++)
    {
        for (int j = 1; j <7; j++)
        {
            m[i][j] = MAX_COUNT;//��ÿ��������������
        }
        m[i][i] = 0;
    }

    //��m[i][j]
    for (int x = 1; x < 6; x++) 
    {
        for (int i = 1, j = x + 1; j <7; i++, j++)
        {
            for (int k = i; k < j; k++) //����kֵ
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
    
    printf("������˴���");
    printResult(1, 6);

    printf("\n���ٳ˷�������%d\n", m[1][6]);

    system("pause");
    return 0;
}
