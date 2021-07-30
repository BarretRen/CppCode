//std::pair的使用示例
#include <iostream>
#include <utility>
#include <tuple>

using namespace std;

class Foo
{
public:
    Foo(tuple<int, float>)
    {
        cout << "Foo::Foo(tuple)" << endl;
    }
    template <typename... Args>
    Foo(Args... args)
    {
        cout << "Foo::Foo(args...)" << endl;
    }
};

int main()
{
    tuple<int, float> t(1, 2.22); //创建一个元组
    //构建Foo时，传入t为元组，所以默认使用第一个构造函数
    pair<int, Foo> p1(1, t);
    //创建pair时限传入了piecewise_construct，表示pair的参数使用不定个数参数的形式
    //所以这里，first为42，Foo构建时使用第二个构造函数
    pair<int, Foo> p2(std::piecewise_construct, make_tuple(2), t);

    //打印一下pair的key-value
    cout << p1.first << endl;//直接打印first，second
    cout << get<0>(p2) << endl;//使用get模板函数
}