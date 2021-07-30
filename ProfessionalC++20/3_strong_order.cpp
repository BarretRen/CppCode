//C++20新增三元比较运算符，一次比较得到得到结果，不需要重复比较原数据
#include <iostream>
#include <compare>
using namespace std;

int main()
{
    int i{11};
    //result保存比较结果，不能用switch比较
    strong_ordering result{i <=> 0};
    if (result == strong_ordering::less)
    {
        cout << "less" << endl;
    }
    if (result == strong_ordering::greater)
    {
        cout << "greater" << endl;
    }
    if (result == strong_ordering::equal)
    {
        cout << "equal" << endl;
    }
    //可以使用辅助函数比较result，不直接不叫枚举类
    if (is_lt(result))
    {
        cout << "less" << endl;
    }
    if (is_gt(result))
    {
        cout << "greater" << endl;
    }
    if (is_eq(result))
    {
        cout << "equal" << endl;
    }
    return 0;
}