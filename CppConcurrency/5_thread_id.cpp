/*
���ֻ�ȡ�̱߳�ʶid�ķ�����id�����ڱȽ��Ƿ���ͬһ�߳�
*/
#include <iostream>
#include <thread>

using namespace std;

void hello();

int main5()
{
	thread th(hello);
	th.join();
	thread::id childId = th.get_id();//��ȡָ���̶߳����id
	thread::id masterId = this_thread::get_id();//��ȡ��ǰ�̵߳�id
	cout << "child thread id:" << childId << endl;
	cout << "master thread id:" << masterId << endl;
	cout << (masterId == childId) << endl;
	
	return 0;
}