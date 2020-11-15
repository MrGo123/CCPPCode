#include <iostream>
using namespace std;
int main()
{
    int a[10], *p1, *p2;
    p1 = a;
    p2 = &a[5];
    cout << p2 - p1 << endl;

    system("pause");
    return 0;
}