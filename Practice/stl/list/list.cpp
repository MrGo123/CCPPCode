#include <iostream>

using namespace std;

typedef struct list
{
    /* data */
    int node;
    list* next;
}node;

int main(){
    node l;
    l.node=1;
    l.next = new node();

    system("pause");
    return 0;
}