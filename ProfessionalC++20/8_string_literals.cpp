//auto�ַ���Ĭ����const char*���ͣ���Ҫ�ֶ��޸Ĳ����Զ��Ƶ�Ϊstd::string
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