#include <stdio.h>
#include <stdlib.h>

int queen[8] = {0}; //行
int count = 0;

//检测是否安全
int Try(int raw, int column)
{
    for (int i = 0; i < raw; i++)
    {
        int currQueen = queen[i];
        if (column == currQueen || (i + currQueen) == (raw + column) || (i - currQueen) == (raw - column))
        //同一列，/斜线方向、\方向
            return 0;
    }
    return 1;
}
//k——皇后
void putQueen(int k)
{
    if (k == 8)
    {
        count++;
        return;
    }
    //为当前这个皇后找一个位置
    for (int i = 0; i < 8; i++)
    {
        queen[k] = i;
        if (Try(k, i)) //判断是否安全
        {
            putQueen(k + 1);
        }
    }
}

int main()
{
    putQueen(0); //从第0行皇后开始
    printf("%d\n", count);
    system("pause");
    return 0;
}