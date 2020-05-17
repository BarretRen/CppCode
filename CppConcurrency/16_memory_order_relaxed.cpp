/*
原子操作的内存顺序：松散序列memory_order_relaxed
*/
#include <atomic>
#include <thread>
#include <iostream>

std::atomic<bool> a, b;
std::atomic<int> c;

void write_x_then_y16()
{
    a.store(true, std::memory_order_relaxed);  // 1
    b.store(true, std::memory_order_relaxed);  // 2
}
void read_y_then_x16()
{
    while (!b.load(std::memory_order_relaxed));  // 3
    if (a.load(std::memory_order_relaxed))  // 4
        ++c;
}
int main16()
{
    a = false;
    b = false;
    c = 0;
    std::thread t1(write_x_then_y16);
    std::thread t2(read_y_then_x16);
    t1.join();
    t2.join();
    std::cout << c.load() << std::endl; // 5
    return 0;
}