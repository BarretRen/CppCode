/*
*使用资源获取即初始化方式”(RAII，Resource Acquisition Is Initialization)，并且提供一个类，在析构函数中使用join()
*/
#include <iostream>
#include <thread>

using namespace std;

class thread_guard
{
private:
	std::thread& t;
public:
	explicit thread_guard(std::thread& t_) : t(t_) {}
	~thread_guard()
	{
		if (t.joinable()) // 1，返回true，说明线程t还没有结束
		{
			t.join();      // 2，此时，主线程需要等待线程t结束，不然局部变量some_local_state会提前释放
		}
	}
	// 3 C++11新特性，不允许编译器自动生成赋值函数和拷贝构造函数
	thread_guard(thread_guard const&) = delete;
	thread_guard& operator=(thread_guard const&) = delete;
};

struct func
{
	int& i;
	func(int& i_) : i(i_) {}
	void operator() ()
	{
		for (unsigned j = 0; j < 1000; ++j)
		{
			cout << "do_something(" << i << ");" << endl;
		}
	}
};

int main2()
{
	int some_local_state = 0;
	func my_func(some_local_state);
	std::thread t(my_func);
	thread_guard g(t);//交给guard类管理线程t的销毁
	cout << "do_something_in_current_thread();" << endl;
	return 0;
}    // 4