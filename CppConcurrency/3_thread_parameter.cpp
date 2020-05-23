/*
*向线程thread中传递参数的几种方式
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
	cout << "str_f，input parameters: " << i << "; " << s << endl;
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
	//1. 基本类型和字符串的传递
	thread t1(str_f, 1, "hello str");
	t1.join();
	//2. 字符串的传递，传递字符指针，需要线转成string，再传递给线程
	char buffer[1024] = { 0 };
	cin >> buffer;
	thread t2(str_f, 2, string(buffer));
	t2.join();
	//3. 结构体的传递
	Data data = { 20,25 };
	//thread t3(struct_f, 3, data);//直接传递结构体，线程无法完成值拷贝，编译不通过
	thread t3(struct_f, 3, std::ref(data));//使用ref，直接传递引用到线程，而不是复制一份
	t3.join();
	//4. 传递类的成员函数和参数
	X my_x;
	std::thread t4(&X::do_work, &my_x, 4);//传递类里函数，对象，和函数所需参数
	t4.join();
	//5. std::move传递指针
	std::unique_ptr<Data> data2(new Data);////唯一智能指针，不可复制
	data2->height = 50;
	data2->weight = 55;
	thread t5(pointer_f, 5, std::move(data2));//指针无法使用std::ref, 使用move转移所有权到线程
	t5.join();
	return 0;
}