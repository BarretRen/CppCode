//C++20������Ԫ�Ƚ��������һ�αȽϵõ��õ����������Ҫ�ظ��Ƚ�ԭ����
#include <iostream>
#include <compare>
using namespace std;

int main()
{
    int i{11};
    //result����ȽϽ����������switch�Ƚ�
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
    //����ʹ�ø��������Ƚ�result����ֱ�Ӳ���ö����
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