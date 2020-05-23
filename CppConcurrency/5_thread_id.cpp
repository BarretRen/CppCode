/*
两种获取线程标识id的方法，id可用于比较是否是同一线程
*/
#include <iostream>
#include <thread>

using namespace std;

void hello();

int main()
{
	thread th(hello);
	th.join();
	thread::id childId = th.get_id();//获取指定线程对象的id
	thread::id masterId = this_thread::get_id();//获取当前线程的id
	cout << "child thread id:" << childId << endl;
	cout << "master thread id:" << masterId << endl;
	cout << (masterId == childId) << endl;
	
	return 0;
}