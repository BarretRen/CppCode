//使用new申请内存时，nothrow可以控制在申请失败时，是否需要抛出异常
#include <iostream>
#include <new>
 
int main()
{
    try {
        while (true) {
            new int[100000000ul];   // 抛出重载
        }
    } catch (const std::bad_alloc& e) {
        std::cout << e.what() << '\n';
    }
 
    while (true) {
        int* p = new(std::nothrow) int[100000000ul]; // 不抛出重载
        if (p == nullptr) {
            std::cout << "Allocation returned nullptr\n";
            break;
        }
    }
}