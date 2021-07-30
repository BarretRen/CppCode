//auto字符串默认是const char*类型，需要手动修改才能自动推导为std::string
#include <string>
#include <iostream>
using namespace std::string_literals;

int main()
{
    auto str1{"string"}; //auto = const char*
    auto str2{"string"s}; //auto = std::string
    // str1[1]='T';
    str2[1]='T';
    std::cout<<str1<<"  "<<str2;
}