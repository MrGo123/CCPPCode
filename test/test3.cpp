#include <iostream>
#include <stack>
#include <vector>
#include <string>
using namespace std;


int main()
{

    int n;
    cin >> n;
    vector<int> a;
    vector<int> b;
    int result = 0;
    
    while (n--)
    {
        int temp;
        cin >> temp;
        a.push_back(temp);
    }
    while (n--)
    {
        int temp;
        cin >> temp;
        b.push_back(temp);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            result += a[i] * b[j];
        }
    }
    cout << result << endl;
    return 0;
}