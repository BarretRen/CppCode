/*
使用std:atomic_flag实现自旋互斥锁
*/
#include <iostream>
#include <thread>
#include <atomic>
#include <vector>

using namespace std;

std::atomic_flag lock = ATOMIC_FLAG_INIT;//初始化

void f(int n)
{
    for (int cnt = 0; cnt < 2; ++cnt) {
        while (lock.test_and_set(std::memory_order_acquire))  // 获得锁
            ; // 如果返回值为清除，则一直循环（自旋）
        std::cout << "Output from thread " << n << '\n';
        lock.clear(std::memory_order_release);               // 释放锁
    }
}

int main()
{
    std::vector<std::thread> v;
    for (int n = 0; n < 10; ++n) {
        v.emplace_back(f, n);
    }
    for (auto& t : v) {
        t.join();
    }
    return 0;
}