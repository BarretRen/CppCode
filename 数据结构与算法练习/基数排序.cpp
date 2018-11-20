/*
基数排序：按照个十百位依次排序
LSD方式
*/
#include <iostream>
#include <list>

using namespace std;


void radixSort(int* data,const int n)
{
    //先计算最大的数是多少位
    int digits = 1; //初始化1位
    int radix = 10;//基数是10
    for (int i=0; i<n; i++)
    {
        while(data[i] >= radix)
        {
            radix *= 10;
            digits++;
        }
    }
    
    list<int> lists[10];//基数10，所以构建10个链表，对应0-9
    int d,j,k,factor; //factor每次*10，用于数组/factor,提取每位
    for (d=1, factor=1; d<=digits; factor*=10, d++)
    {
        //内循环：将数组的数按照每位排序，放入对应index链表中
        for(j=0; j<n; j++)
        {
            //将数组的数，放到每位的值对应的index中
            lists[(data[j]/factor)%10].push_back(data[j]);
        }
        //内循环2：循环每个链表将链表中数放回数组
        for(j=0, k=0; j<10; j++)
        {
            //一个链表可能有多个值，需要循环
            while(!lists[j].empty())
            {
                data[k] = lists[j].front();
                k++;
                lists[j].pop_front();
            }
        }
    }
}

int main()
{
    int data[] = {179,208,306,93,859,984,55,9,271,33};
    radixSort(data, 10);
    
    for(int i=0; i<10; i++)
        cout<<data[i]<<"   ";
    
    return 0;
}