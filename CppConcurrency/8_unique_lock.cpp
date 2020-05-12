/*
std::unique_lock����lock_guard�������������
*/

#include <iostream>
#include <thread>
#include <mutex>

struct Box {
	explicit Box(int num) : num_things(num) {}// explicit���ڹ��캯������Ϊ��������ʽ����ת��

	int num_things;
	std::mutex m;
};

void transfer(Box& from, Box& to, int num)
{
	//����unique_lock
	std::unique_lock<std::mutex> lock1(from.m, std::defer_lock);
	std::unique_lock<std::mutex> lock2(to.m, std::defer_lock);
	//ʹ��std::lock��ȡ����������������
	std::lock(lock1, lock2);

	from.num_things -= num;
	to.num_things += num;
	std::cout << "from:" << from.num_things << ", to:" << to.num_things << std::endl;
	//lock1, lock2������ʱ���Զ�����
}

int main8()
{
	Box b1(100);
	Box b2(50);

	std::thread t1(transfer, std::ref(b1), std::ref(b2), 10);
	std::thread t2(transfer, std::ref(b1), std::ref(b2), 5);

	t1.join();
	t2.join();
	return 0;
}