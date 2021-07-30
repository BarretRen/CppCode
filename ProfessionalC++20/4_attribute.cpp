//C++ attributes使用示例
#include <iostream>
using namespace std;

//使用nodiscard属性，返回值必须被处理使用
[[nodiscard("barret")]] int func1()
{
    return 1;
}

//使用maybe_unused属性，关闭未使用的告警
int func2(int a, [[maybe_unused]] int b)
{
    return 2;
}

//noreturn属性，表示函数调用栈不会返回
[[noreturn]] void forceExitProgram()
{
    std::exit(1); //结束进程
}
bool isIdLicensed(int id)
{
    if (true)
        forceExitProgram();
    else
        return true;
}

//deprecated属性，表示该C++元素被弃用
[[deprecated]] int func3()
{
    return 3;
}

//no_uniqure_address属性
struct A
{
}; // 空类型

struct B
{
    long long v;
    [[no_unique_address]] A a, b;
};

int main()
{
    // func1(); //编译告警
    // forceExitProgram();
    // func2(1, 2);
    // // bool isLicensed{isIdLicensed(42)};
    // cout << func3() << endl;

    // int input = 0;
    // cout << "input a value:";
    // cin >> input;
    // switch (input)
    // {
    //     [[unlikely]] case 0 : //表示该分支发生可能性很小
    //         cout << "i am 0"<<endl;
    //         break;
    //     [[likely]] case 1: //表示该分支很可能发生
    //         cout << "i am 1"<<endl;
    //         [[fallthrough]] //故意不加break；
    //     default:
    //         cout << "i am not 0"<<endl;
    //         break;
    // }

    //使用struct B
    B b;
    std::cout << &b.v << std::endl;      // 输出v地址
    std::cout << &b.a << std::endl;      // a地址为 &v + 1
    std::cout << &b.b << std::endl;      // b地址为 &v + 2
    std::cout << sizeof(B) << std::endl; // 输出 16
}