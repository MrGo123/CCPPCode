#include <stdio.h>
#include <stdlib.h>

int queen[8] = {0}; //��
int count = 0;

//����Ƿ�ȫ
int Try(int raw, int column)
{
    for (int i = 0; i < raw; i++)
    {
        int currQueen = queen[i];
        if (column == currQueen || (i + currQueen) == (raw + column) || (i - currQueen) == (raw - column))
        //ͬһ�У�/б�߷���\����
            return 0;
    }
    return 1;
}
//k�����ʺ�
void putQueen(int k)
{
    if (k == 8)
    {
        count++;
        return;
    }
    //Ϊ��ǰ����ʺ���һ��λ��
    for (int i = 0; i < 8; i++)
    {
        queen[k] = i;
        if (Try(k, i)) //�ж��Ƿ�ȫ
        {
            putQueen(k + 1);
        }
    }
}

int main()
{
    putQueen(0); //�ӵ�0�лʺ�ʼ
    printf("%d\n", count);
    system("pause");
    return 0;
}