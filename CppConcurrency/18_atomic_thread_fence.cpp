#include <atomic>
#include <thread>
#include <assert.h>
#include <iostream>

std::atomic<bool> x, y;
std::atomic<int> z;

void write_x_then_y()
{
    x.store(true, std::memory_order_relaxed);            // 1 设置x为true
    std::atomic_thread_fence(std::memory_order_release); // 2 释放栅栏
    y.store(true, std::memory_order_relaxed);            // 3 设置y为true
}

void read_y_then_x()
{
    while (!y.load(std::memory_order_relaxed))
        ;                                                // 4 等待y为true时退出循环
    std::atomic_thread_fence(std::memory_order_acquire); // 5 获取栅栏
    if (x.load(std::memory_order_relaxed))               // 6 读取x的值
        ++z;
}

int main()
{
    x = false;
    y = false;
    z = 0;
    std::thread a(write_x_then_y);
    std::thread b(read_y_then_x);
    a.join();
    b.join();
    assert(z.load() != 0); // 7 z=1,断言不会触发
}