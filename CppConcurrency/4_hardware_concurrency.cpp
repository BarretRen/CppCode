/*
ͨ��std::thread::hardware_concurrency()��ȡϵͳ֧�ֵ�����߳���
*/
#include <iostream>
#include <thread>

int main4() {
	unsigned int n = std::thread::hardware_concurrency();
	std::cout << n << " concurrent threads are supported.\n";

	return 0;
}