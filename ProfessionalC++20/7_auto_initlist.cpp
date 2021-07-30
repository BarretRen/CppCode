//复制初始化列表和直接初始化列表的区别
//C++17之后可能导致编译错误
#include <initializer_list>

int main()
{
    // Copy list initialization
    auto a = {11};     // auto = initializer_list<int>
    auto b = {11, 22}; // auto = initializer_list<int>

    // Direct list initialization
    auto c{11};     // auto = int
    auto d{11, 22}; // auto = int不能有多个值. Error, too many elements.
}