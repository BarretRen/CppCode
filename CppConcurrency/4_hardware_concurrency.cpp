/*
通过std::thread::hardware_concurrency()获取系统支持的最大线程数
*/
#include <iostream>
#include <thread>

int main() {
	unsigned int n = std::thread::hardware_concurrency();
	std::cout << n << " concurrent threads are supported.\n";

	return 0;
}