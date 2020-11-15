#include <iostream>
#include <stack>
#include <string>
using namespace std;

int judge(string &s)
{
    for (int i = 0, j = s.length() - 1; i <= j; i++, j--)
    {
        if ((int)s[i] == (int)s[j])
        {
            continue;
        }
        else
        {
            return 0;
        }
    }

    return 1;
}

int main()
{

    int n, count = 0;
    cin >> n;
    int result[n];
    while (n--)
    {
        string s;
        cin >> s;
        if (judge(s))
        {
            cout << "Yes" << endl;
        }
        else
        {
            cout << "Nope" << endl;
        }
    }
    return 0;
}