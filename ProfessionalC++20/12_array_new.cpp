//��ͨ���͵����飬ʹ��new[]/delete[]���ɡ��������ӵĶ�ά���鲻��������
//���ڱ���ָ������飬deleteʱ��Ҫ����һ��һ��delete[]�����delete[]��������
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
    //��ʼdelete�ڴ�
    for (int i = 0; i < size; i++)
    {
        delete[] ptrArray[i]; //delete�ڲ��ַ
        ptrArray[i] = nullptr;
    }
    delete[] ptrArray;//delete���ϲ��ַ
    ptrArray = nullptr;
    return 0;
}