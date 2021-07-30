//std::optional使用示例，表示可以存在或不存在的值
#include <iostream>
#include <optional>

using namespace std;

//定义一个函数，返回值是可选值，既可以是int，也可以是其他非类型
optional<int> getData(bool it)
{
    if (it)
        return 42;
    return nullopt;
}

int main()
{
    //调用函数，保存返回值
    optional<int> data1{getData(true)};
    optional<int> data2{getData(false)};
    //判断变量是否有值(两种方式)，如果有打印值
    if (data1.has_value())
    {
        cout << data1.value() << endl;
    }
    if (data2)
    {//不经判断直接访问会抛出exception
        cout << *data2 << endl;
    }
    //data2没有值，但可以通过以下方式打印它保存了什么
    cout << "what is in data? " << data2.value_or(0) << endl;
}