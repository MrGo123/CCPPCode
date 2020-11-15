#include <iostream>
#include <stack>
#include <vector>
#include <string>
using namespace std;

vector<int> v;

int arrdevide(int low, int high)
{
    int pivot = v[low];
    while (low < high)
    {
        while (low < high && v[high] >= pivot)
        {
            --high;
        }
        v[low] = v[high];
        while (low < high && v[low] <= pivot)
        {
            ++low;
        }
        v[high] = v[low];
    }
    v[low] = pivot;
    return low;
}

void quickSort(int low, int high)
{
    if (low < high)
    {
        int pivot = arrdevide(low, high);
        quickSort(low, pivot - 1);
        quickSort(pivot + 1, high);
    }
}

int main()
{
    int n;
    cin >> n;
    int temp;
    while (n--)
    {
        cin >> temp;
        v.push_back(temp);
    }
    quickSort(0, v.size());
    int max = v[v.size() - 1];
    for (int i = v.size() - 1; i >= 0; i--)
    {
        if (v[i] == max)
        {
            v.erase(v.begin() + i);
        }
        else
        {
            break;
        }
    }
    cout << v[v.size() - 1] << endl;
    system("pause");
    return 0;
}