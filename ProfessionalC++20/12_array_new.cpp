//普通类型的数组，使用new[]/delete[]即可。下面例子的二维数组不能这样做
//对于保存指针的数组，delete时需要遍历一个一个delete[]，最后delete[]整个数组
#include <iostream>

using namespace std;

int main()
{
    const int size{4};
    int **ptrArray{new int *[size]};
    for (int i = 0; i < size; i++)
    {
        ptrArray[i] = new int[size]{i};
    }
    //开始delete内存
    for (int i = 0; i < size; i++)
    {
        delete[] ptrArray[i]; //delete内层地址
        ptrArray[i] = nullptr;
    }
    delete[] ptrArray;//delete最上层地址
    ptrArray = nullptr;
    return 0;
}