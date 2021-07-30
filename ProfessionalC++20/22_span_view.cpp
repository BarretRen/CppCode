//演示span视图的使用
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
    //直接传vector，因隐式转换为全范围的span
    print(v);

    //创建全范围span作为参数
    span mySpan{v};
    print(mySpan);

    //从全范围span创建子span
    span subspan{mySpan.subspan(2, 3)};
    print(subspan);

    //从vector创建span，因为第一个参数是指针，所以需要调用data()
    print({v.data() + 2, 3});

    //从array创建span
    array<int, 5> arr{5, 4, 3, 2, 1};
    print(arr);
    print({arr.data() + 2, 3});

    //从C数组创建span
    int carr[]{9, 8, 7, 6, 5};
    print(carr);          // The entire C-style array.
    print({carr + 2, 3}); // A subview of the C-style array.
}