#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
using namespace std;

int *selectSort(int *arr, int n)
{

    for (int i = 0; i < n; i++)
    {
        int max = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[max] > arr[j])
            {
                max = j;
            }
        }
        if (i == max)
        {
            continue;
        }
        int temp = arr[i];
        arr[i] = arr[max];
        arr[max] = temp;
    }
    return arr;
}

int ResurHalfDevide(int *arr, int left, int right, int target)
{

    if (left > right)
        return -1;
    int mid = (left + right) / 2;

    if (arr[mid] == target)
        return mid;
    else if (arr[mid] < target)
    {
        return ResurHalfDevide(arr, mid + 1, right, target);
    }
    else
    {
        return ResurHalfDevide(arr, left, mid - 1, target);
    }
}

int main(void)
{

    int arr[20];
    int *sorted = NULL;
    srand((unsigned)time(NULL));

    // 生成20个随机数
    for (int i = 0; i < 20; i++)
    {
        arr[i] = rand() % 100 + 1;
    }
    cout<<"random number list: ";
    for (int i : arr)
    {
        cout << i << "  ";
    }
    cout<<endl;

    //进行选择排序
    selectSort(arr, 20);
    cout<<"Sorted number list: ";
    for (int i : arr)
    {
        cout << i << "  ";
    }
    cout<<endl;

    //进行查找
    cout<<"Searching number: ";
    int queryNum;
    cin >> queryNum;

    // 递归二分查找
    int res = ResurHalfDevide(arr, 0, 19, queryNum);
    
    //输出结果
    if (res == -1)
    {
        cout << "Didn't find " << queryNum << endl;
    }
    else
    {
        cout << "found " << queryNum << " index = " << res << endl;
    }

    system("pause");
    return 0;
}
