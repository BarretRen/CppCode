/*
*ʹ����Դ��ȡ����ʼ����ʽ��(RAII��Resource Acquisition Is Initialization)�������ṩһ���࣬������������ʹ��join()
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
		if (t.joinable()) // 1������true��˵���߳�t��û�н���
		{
			t.join();      // 2����ʱ�����߳���Ҫ�ȴ��߳�t��������Ȼ�ֲ�����some_local_state����ǰ�ͷ�
		}
	}
	// 3 C++11�����ԣ�������������Զ����ɸ�ֵ�����Ϳ������캯��
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
	thread_guard g(t);//����guard������߳�t������
	cout << "do_something_in_current_thread();" << endl;
	return 0;
}    // 4