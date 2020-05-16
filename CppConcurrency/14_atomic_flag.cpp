/*
ʹ��std:atomic_flagʵ������������
*/
#include <iostream>
#include <thread>
#include <atomic>
#include <vector>

using namespace std;

std::atomic_flag lock = ATOMIC_FLAG_INIT;//��ʼ��

void f(int n)
{
    for (int cnt = 0; cnt < 2; ++cnt) {
        while (lock.test_and_set(std::memory_order_acquire))  // �����
            ; // �������ֵΪ�������һֱѭ����������
        std::cout << "Output from thread " << n << '\n';
        lock.clear(std::memory_order_release);               // �ͷ���
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