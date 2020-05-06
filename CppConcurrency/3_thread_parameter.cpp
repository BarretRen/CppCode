/*
*���߳�thread�д��ݲ����ļ��ַ�ʽ
*/
#include <iostream>
#include <thread>
#include <string>

using namespace std;

struct Data
{
	int height;
	int weight;
};

class X
{
public:
	void do_work(int i)
	{
		cout << "I am a function in class X, input parameter: " << i << endl;
	}
};

void str_f(int i, string const& s)
{
	cout << "str_f��input parameters: " << i << "; " << s << endl;
}

void struct_f(int i, Data& data)
{
	cout << "struct_f, input parameters: "<< i << "; height:" << data.height << ", weight:" << data.weight << endl;
}

void pointer_f(int i, std::unique_ptr<Data> data)
{
	cout << "pointer_f, input parameters: " << i << "; height:" << data->height << ", weight:" << data->weight << endl;
}

int main()
{
	//1. �������ͺ��ַ����Ĵ���
	thread t1(str_f, 1, "hello str");
	t1.join();
	//2. �ַ����Ĵ��ݣ������ַ�ָ�룬��Ҫ��ת��string���ٴ��ݸ��߳�
	char buffer[1024] = { 0 };
	cin >> buffer;
	thread t2(str_f, 2, string(buffer));
	t2.join();
	//3. �ṹ��Ĵ���
	Data data = { 20,25 };
	//thread t3(struct_f, 3, data);//ֱ�Ӵ��ݽṹ�壬�߳��޷����ֵ���������벻ͨ��
	thread t3(struct_f, 3, std::ref(data));//ʹ��ref��ֱ�Ӵ������õ��̣߳������Ǹ���һ��
	t3.join();
	//4. ������ĳ�Ա�����Ͳ���
	X my_x;
	std::thread t4(&X::do_work, &my_x, 4);//�������ﺯ�������󣬺ͺ����������
	t4.join();
	//5. std::move����ָ��
	std::unique_ptr<Data> data2(new Data);////Ψһ����ָ�룬���ɸ���
	data2->height = 50;
	data2->weight = 55;
	thread t5(pointer_f, 5, std::move(data2));//ָ���޷�ʹ��std::ref, ʹ��moveת������Ȩ���߳�
	t5.join();
	return 0;
}