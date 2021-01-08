#include <stdio.h>
#include <stdlib.h>
int queensVolum[8] = {0}, num = 0;

//检查是否能放在这个位置
int Try(int line, int colum)
{
    for (int i = 0; i < line; i++)
    {
        int currQueen = queensVolum[i];
        if ((colum == currQueen) || (i + currQueen) == (line + colum) || (i - currQueen) == (line - colum)) //同一列、斜上方、斜下方
        {
            return 0;
        }
    }
    return 1;
}
void queene(int line)
{
    for (int colum = 0; colum < 8; colum++)
    {
        if (Try(line, colum))
        {
            queensVolum[line] = colum;
            if (line == 7)
            {
                num++;
                queensVolum[line] = 0;
                return;
            }
            queene(line + 1);
            queensVolum[line] = 0;
        }
    }
}
int main()
{
    queene(0);
    printf("%d", num);
    system("pause");
    return 0;
}
