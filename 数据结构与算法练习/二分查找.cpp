/*
二分查找
二分查找 with 迭代
*/
#include <iostream>

using namespace std;

int binarySearch(int* a, const int x, const int n)
{
    int low = 0;
    int high = n - 1;
    int middle;
    
    while(low <= high)
    {
        middle = (low + high) / 2;
        cout<<a[middle]<<"  ";
        if (a[middle] == x)
        {
            cout<<endl;
            return middle;
        }
        else if (a[middle] < x)
        {
            //中间值小于要查找的值，所以要搜索后一半
            low = middle + 1;
        }
        else
        {
            //中间值大于要查找的值，所以要搜索前一半
            high = middle - 1;
        }
    }
    cout<<endl;
    return -1; //没找到返回-1
}

//递归实现二分查找
int binarySearchWithR(int* a, const int x, const int low, const int high)
{
    if (low <= high)
    {
        int middle = (low + high) / 2;
        cout<<middle<<"  "<<a[middle]<<endl;
        if (a[middle] == x)
        {
            return middle;
        }
        else if(a[middle] < x)
        {
            return binarySearchWithR(a, x, middle + 1, high);
        }
        else
        {
            return binarySearchWithR(a, x, low, middle - 1);
        }
    }
    else
    {
        return -1;
    }
}
int main()
{
    int array[] = {1,2,3,4,5,6,7,8,9,10};
    
    cout<<binarySearchWithR(array, 7, 0, 9)<<endl;
    
    return 0;
}