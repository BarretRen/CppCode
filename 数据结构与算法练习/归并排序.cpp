/*
归并排序
*/

#include <iostream>
#include <algorithm>

using namespace std;

//合并函数，将包含两个排好序的数组合并到另一个数组
//l=第一个已经排好序的第一个数的index
//m=第一个已排好序的最后一个数的index
//n=两个已排序子数组的总个数
template<class T>
void merge(T* initList, T* mergedList, const int l, const int m, const int n)
{
    int i1;//第一个排好序的子数组index
    int i2;//第二个排好序的子数组的index
    int iResult; //合并后数组的index
    for (i1=l, i2=m+1, iResult=l; i1<=m && i2<=n-1; iResult++)
    {
        if(initList[i1] <= initList[i2])
        {
            //I1小，合并数组里先放i1
            mergedList[iResult] = initList[i1];
            i1++;
        }
        else
        {
            //I2小，合并数组里先放i1
            mergedList[iResult] = initList[i2];
            i2++;
        }     
    }
    //由于两个已排序子数组不一定一样长，所以需要将剩下的数复制到mergedList
    copy(initList + i1, initList + m + 1, mergedList + iResult); //复制第一个子数组剩下的，没有的话copy函数直接返回
    copy(initList + i2, initList + n, mergedList + iResult); //复制第一个子数组剩下的，没有的话copy函数直接返回
}

//一次归并函数
//n=initList的个数
//s为每次归并前当前每个已排序子数组的个数
template<class T>
void mergeOnce(T* initList, T* resultList, const int n, const int s)
{
    int i;
    for(i=0; i<n-2*s+1; i+=2*s)
    {
        merge(initList, resultList, i, i+s-1, i+2*s);
    }
    //如果有剩余没有和它归并的,就复制到末尾
    if ((i+s-1) < n)
    {
        merge(initList, resultList, i, i+s-1, n);
    }
    else
    {
        copy(initList+i, initList+n, resultList+i);
    }   
    //打印一下归并后结果
    cout<<"after merge once:  ";
    for(int i = 0; i < n; i++)
        cout<<resultList[i]<<"   ";
    cout<<endl;
}

//归并排序算法
//n=数组个数
template<class T>
void mergeSort(T* a, const int n)
{
    T* tmpList = new int[n];
    for(int s=1; s<n; s*=2)  //这里s和mergeOnce里s含义相同
    {
        //一次循环调用两次，这样只用a,tmpList两个数组
        mergeOnce(a, tmpList, n, s);
        s *= 2;
        mergeOnce(tmpList, a, n, s);
    }
    delete tmpList;
}

int main()
{    
    int m[]={26,5,77,1,61,11,59,15,48,19}; //要排序的数组
    mergeSort(m, 10);
    
    cout<<endl;
    for(int i = 0; i < 10; i++)
        cout<<m[i]<<"   ";
    cout<<endl;
    
    return 0;
}