/*
冒泡排序：
从左向右扫描，比较相邻的两个数据，如果左边数据大于右边，就互换位置
*/
#include <iostream>

using namespace std;

void bubbleSort(int list[], int n)
{
    int num = 0;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (list[i] > list[j])
            {
                swap(list[i], list[j]);
            }
        }
    }
}

int main()
{
    int a[]={2,4,6,5,3,1,9,7,10,8};
    bubbleSort(a, 10);

    for(int i = 0; i < 10; i++)
        cout<<a[i]<<"   ";

    return 0;
}