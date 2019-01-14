/*
快速排序
1.选择一个数作为枢轴
2.小于枢轴的数放在左边，大于枢轴的数放在右边。（具体执行为：从首尾同步进行，从首选择比枢轴大的，从尾选比枢轴小的，然后互换位置）
3.对左边的数，继续选枢轴，继续步骤2（递归）
4.对右边的数，继续选枢轴，继续步骤2（递归）
*/
#include <iostream>

using namespace std;

template<class T>
void quickSort(T* a, const int leftIdx, const int rightIdx)
{
    if (leftIdx < rightIdx)
    {
        //选择枢轴,选择第一个数
        int i = leftIdx + 1;//左边起始位置跳过枢轴
        int j = rightIdx;
        int keyValue = a[leftIdx];
        
        while(i < j)//跳出循环时，i=j，处于中间位置
        {    
            while(a[i] < keyValue)
            {
                //左边开始，如果数小于枢轴，继续增加index
                i++;
            }
            while(a[j] > keyValue)
            {
                //右边开始，如果数大于枢轴，继续减小index
                j--;
            }
            if (i < j)
            {
                //如果i<j, 说明数没有交叉，需要互换位置
                swap(a[i],a[j]);
            }
        }
        //将之前选定的枢轴移动中间位置
        //如果不移动枢轴，下次枢轴就还是这个值，没法继续排序下去
        swap(a[leftIdx], a[j]);
        
        //对左边，右边进行递归
        quickSort(a, leftIdx, j -1);
        quickSort(a, j + 1, rightIdx);
    }
}

int main()
{
    int a[]={2,4,6,5,3,1,9,7,10,8,12,25,99,67};
    quickSort(a, 0, 13);

    for(int i = 0; i <= 13; i++)
        cout<<a[i]<<"   ";
    cout<<endl;
    return 0;
}