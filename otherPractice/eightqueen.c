#include <stdio.h>
#include <stdlib.h>

int queens[8] = {0};
int num = 0;

int check(int raw, int column)
{
    for (int i = 0; i < raw; i++)
    {
        //同一列，已放皇后位于左上角，已放皇后位于右上角
        if ((queens[i] == column) || ((i - queens[i]) == (raw - column)) || (i+queens[i])==(raw+column)){
            return 0;
        }
    }
    return 1;
}

void putQueen(int queenIndex)
{
    if (queenIndex == 8) //如果能够进入第九个皇后到这一步，说明前面的8个皇后均已放置。
    {
        
        num++;
        return;
    }

    for (int i = 0; i < 8; i++)
    {
        if (check(queenIndex, i)) //检测这个位置是否安全
        {
            queens[queenIndex] = i;   //安全，放置皇后
            putQueen(queenIndex + 1); //进行下一个皇后的判断
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