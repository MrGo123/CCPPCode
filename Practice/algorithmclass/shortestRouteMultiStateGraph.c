#include <stdio.h>
#include <stdlib.h>
#define N 10

int main(){

    int graph[N][N]={
        {0,4,2,3,0,0,0,0,0,0},
        {0,0,0,0,10,9,0,0,0,0},
        {0,0,0,0,6,7,10,0,0,0},
        {0,0,0,0,0,3,8,0,0,0},
        {0,0,0,0,0,0,0,4,8,0},
        {0,0,0,0,0,0,0,9,6,0},
        {0,0,0,0,0,0,0,5,4,0},
        {0,0,0,0,0,0,0,0,0,8},
        {0,0,0,0,0,0,0,0,0,4},
        {0,0,0,0,0,0,0,0,0,0},
        };
    int shortest[N]={1000};
    int preNode[N]={0};

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d ",graph[i][j]);
        }
        printf("\n");

    }
    
    printf("shortestCost= ",shortest[9]);
    
    


    system("pause");
    return 0;
}