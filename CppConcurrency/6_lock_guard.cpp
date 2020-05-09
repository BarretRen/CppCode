/*
使用互斥量mutex和lock_guard进行加锁解锁操作。
lock_guard可以自动进行加锁解锁，不需要手动调用lock和unlock
*/

#include <iostream>
#include <thread>
#include <mutex>

int gloabl_v = 0;//全局变量
std::mutex g_v_mutex;//定义一个互斥量用于保护全局变量

void add_global_v()
{
	//定义一个lock_guard，自动加锁
	std::lock_guard<std::mutex> my_lock(g_v_mutex);
	gloabl_v++;

	std::cout << std::this_thread::get_id() << " : " << gloabl_v << std::endl;
	//my_lock被释放时，互斥量会自动解锁
}

int main6()
{
	std::cout <<  "main : " << gloabl_v << std::endl;

	std::thread t1(add_global_v);
	t1.join();
	
	std::thread t2(add_global_v);
	t2.join();

	std::cout << "main : " << gloabl_v << std::endl;
	return 0;
}