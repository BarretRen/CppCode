#include <tuple>
#include <iostream>
#include <complex>
#include <string>

using namespace std;

int main()
{
    //创建并初始化tuple
    tuple<int, float, string> t1{41, 6.3, "nice"};
    //打印值
    cout << get<0>(t1) << "  ";
    cout << get<1>(t1) << "  ";
    cout << get<2>(t1) << "  ";
    cout << endl;

    //使用make_tuple创建tuple
    auto t2 = make_tuple(22, 33, "nice");
    cout << get<0>(t2) << "  ";
    cout << get<1>(t2) << "  ";
    cout << get<2>(t2) << "  ";
    cout << endl;

    //给元组第二个值赋值
    get<1>(t1) = 44;
    cout << get<1>(t1) << "  ";

    //比较元组大小
    cout << "is t1 > t2: " << (t1 > t2) << endl;

    //使用tie解包
    int a;
    string s;
    std::tie(a, std::ignore, s) = t1; //ignore为略过部分成员
    cout << a << "  " << s << endl;
}