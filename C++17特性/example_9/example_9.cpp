#include <iostream>
#include <functional>

int foo(int a)
{
    return a;
}

int main()
{
    std::function<int(int)> func = foo; //包装了一个返回值为int，参数为int的函数

    int important = 10;
    std::function<int(int)> func2 = [&](int value)->int{
        return 1 + value + important;
    };

    std::cout<<func(10)<<std::endl;
    std::cout<<func2(10)<<std::endl;

}
