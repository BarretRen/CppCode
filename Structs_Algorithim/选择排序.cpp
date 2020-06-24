/*
选择排序：
从当前未排序的数组中选择最小的数，放到已经排序的数组中.
和冒泡排序相同复杂度
*/
#include <iostream>

using namespace std;

void selectSort(int list[], int n)
{
    int minIdx = 1;
    for (int i=0; i < n - 1; i++)
    {
        minIdx = i;
        for (int j = i+1; j < n; j++)
        {
            if (list[j] < list[minIdx])
            {
                minIdx = j;
            }
        }
        swap(list[i], list[minIdx]);
    }
}

int main()
{
    int a[]={2,4,6,5,3,1,9,7,10,8};
    selectSort(a, 10);
	
    for(int i = 0; i < 10; i++)
        cout<<a[i]<<"   ";
	
    return 0;
}