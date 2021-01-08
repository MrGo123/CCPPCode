#include <stdio.h>
#include <stdlib.h>

int queens[8] = {0};
int num = 0;

int check(int raw, int column)
{
    for (int i = 0; i < raw; i++)
    {
        //ͬһ�У��ѷŻʺ�λ�����Ͻǣ��ѷŻʺ�λ�����Ͻ�
        if ((queens[i] == column) || ((i - queens[i]) == (raw - column)) || (i+queens[i])==(raw+column)){
            return 0;
        }
    }
    return 1;
}

void putQueen(int queenIndex)
{
    if (queenIndex == 8) //����ܹ�����ھŸ��ʺ���һ����˵��ǰ���8���ʺ���ѷ��á�
    {
        
        num++;
        return;
    }

    for (int i = 0; i < 8; i++)
    {
        if (check(queenIndex, i)) //������λ���Ƿ�ȫ
        {
            queens[queenIndex] = i;   //��ȫ�����ûʺ�
            putQueen(queenIndex + 1); //������һ���ʺ���ж�
        }
    }
}

int main()
{
    putQueen(0);
    printf("%d\n", num);
    system("pause");
    return 0;
}