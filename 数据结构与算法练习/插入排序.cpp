/*
插入排序
从第二个数开始与前面数进行比较，前面数大就移动到后面，与前面所有数比较之后，就可以确定当前数要插入的位置，然后插入。
这样数组前面的数都是排好序的。
插入排序比冒泡和选择排序循环次数少
*/
#include <iostream>

using namespace std;

void insertSort(int *a, const int n)
{
    int sorted; //已经排好序的个数
    int in; //即将参与排序的
    int count = 0; //循环进程次数
    //默认index=0第一个数已经排好，所以即将参与排序的从第二个开始
    for (in = 1; in < n; in++)
    {
        int inValue = a[in]; //要参与排序的值
        sorted = in;
        while(sorted > 0 && a[sorted - 1] >= inValue)
        {
            //如果已经有排好序的，并且排好序的最后一个大于当前要参与排序的，则最后一个向后移动一位
            a[sorted] = a[sorted - 1];
            sorted--;
            count++;
        }
        //循环结束，已经比较了一边，当前sorted的位置就是in数需要插入的位置
        a[sorted] = inValue;
    }
    cout<<count<<endl;
}

int main()
{
    int a[]={2,4,6,5,3,1,9,7,10,8};
    insertSort(a, 10);

    for(int i = 0; i < 10; i++)
        cout<<a[i]<<"   ";

    return 0;
}