/*
ʹ�û�����mutex��lock_guard���м�������������
lock_guard�����Զ����м�������������Ҫ�ֶ�����lock��unlock
*/

#include <iostream>
#include <thread>
#include <mutex>

int gloabl_v = 0;//ȫ�ֱ���
std::mutex g_v_mutex;//����һ�����������ڱ���ȫ�ֱ���

void add_global_v()
{
	//����һ��lock_guard���Զ�����
	std::lock_guard<std::mutex> my_lock(g_v_mutex);
	gloabl_v++;

	std::cout << std::this_thread::get_id() << " : " << gloabl_v << std::endl;
	//my_lock���ͷ�ʱ�����������Զ�����
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