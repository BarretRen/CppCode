//��ʾspan��ͼ��ʹ��
#include <iostream>
#include <span>
#include <vector>
#include <array>
using namespace std;

void print(span<int> values)
{
    for (const auto &value : values)
    {
        cout << value << " ";
    }
    cout << endl;
}

int main()
{
    vector v{11, 22, 33, 44, 55, 66};
    //ֱ�Ӵ�vector������ʽת��Ϊȫ��Χ��span
    print(v);

    //����ȫ��Χspan��Ϊ����
    span mySpan{v};
    print(mySpan);

    //��ȫ��Χspan������span
    span subspan{mySpan.subspan(2, 3)};
    print(subspan);

    //��vector����span����Ϊ��һ��������ָ�룬������Ҫ����data()
    print({v.data() + 2, 3});

    //��array����span
    array<int, 5> arr{5, 4, 3, 2, 1};
    print(arr);
    print({arr.data() + 2, 3});

    //��C���鴴��span
    int carr[]{9, 8, 7, 6, 5};
    print(carr);          // The entire C-style array.
    print({carr + 2, 3}); // A subview of the C-style array.
}