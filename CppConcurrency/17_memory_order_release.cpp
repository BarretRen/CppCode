/*
原子操作的内存顺序：获取释放序列memory_order_release
*/
#include <atomic>
#include <thread>
#include <assert.h>
#include <iostream>

std::atomic<bool> x17, y17;
std::atomic<int> z17;
void write_x17()
{
    x17.store(true, std::memory_order_release);
}
void write_y17()
{
    y17.store(true, std::memory_order_release);
}
void read_x_then_y17()
{
    while (!x17.load(std::memory_order_acquire));
    if (y17.load(std::memory_order_acquire))  // 1
        ++z17;
}
void read_y_then_x17()
{
    while (!y17.load(std::memory_order_acquire));
    if (x17.load(std::memory_order_acquire))  // 2
        ++z17;
}
int main()
{
    x17 = false;
    y17 = false;
    z17 = 0;
    std::thread a17(write_x17);
    std::thread b17(write_y17);
    std::thread c17(read_x_then_y17);
    std::thread d17(read_y_then_x17);
    a17.join();
    b17.join();
    c17.join();
    d17.join();
    std::cout << z17.load() << std::endl; // 3
}