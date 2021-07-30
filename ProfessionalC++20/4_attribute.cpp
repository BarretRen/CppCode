//C++ attributesʹ��ʾ��
#include <iostream>
using namespace std;

//ʹ��nodiscard���ԣ�����ֵ���뱻����ʹ��
[[nodiscard("barret")]] int func1()
{
    return 1;
}

//ʹ��maybe_unused���ԣ��ر�δʹ�õĸ澯
int func2(int a, [[maybe_unused]] int b)
{
    return 2;
}

//noreturn���ԣ���ʾ��������ջ���᷵��
[[noreturn]] void forceExitProgram()
{
    std::exit(1); //��������
}
bool isIdLicensed(int id)
{
    if (true)
        forceExitProgram();
    else
        return true;
}

//deprecated���ԣ���ʾ��C++Ԫ�ر�����
[[deprecated]] int func3()
{
    return 3;
}

//no_uniqure_address����
struct A
{
}; // ������

struct B
{
    long long v;
    [[no_unique_address]] A a, b;
};

int main()
{
    // func1(); //����澯
    // forceExitProgram();
    // func2(1, 2);
    // // bool isLicensed{isIdLicensed(42)};
    // cout << func3() << endl;

    // int input = 0;
    // cout << "input a value:";
    // cin >> input;
    // switch (input)
    // {
    //     [[unlikely]] case 0 : //��ʾ�÷�֧���������Ժ�С
    //         cout << "i am 0"<<endl;
    //         break;
    //     [[likely]] case 1: //��ʾ�÷�֧�ܿ��ܷ���
    //         cout << "i am 1"<<endl;
    //         [[fallthrough]] //���ⲻ��break��
    //     default:
    //         cout << "i am not 0"<<endl;
    //         break;
    // }

    //ʹ��struct B
    B b;
    std::cout << &b.v << std::endl;      // ���v��ַ
    std::cout << &b.a << std::endl;      // a��ַΪ &v + 1
    std::cout << &b.b << std::endl;      // b��ַΪ &v + 2
    std::cout << sizeof(B) << std::endl; // ��� 16
}