//��Ϊstring_viewֻ��һ��ֻ����ͼ�������ڸ����ַ�������Ϊ�������������ӻ��string��
#include <iostream>
#include <string>
#include <string_view>
#include <ctime>
using namespace std::string_view_literals; //����ʹ��sv���


int main(int argc, char const* argv[])
{
	auto view = "it is a test"sv;//sv��ʾ�ַ�����string_view����
	std::string str = "it is a test";

	std::clock_t time1 = clock();
	for (int i = 0; i < 1000000; i++)
	{
		auto s1 = view.substr(3);
	}
	std::clock_t time2 = clock();
	std::cout << static_cast<double>(time2 - time1) / CLOCKS_PER_SEC * 1000 << std::endl;

	time1 = clock();
	for (int i = 0; i < 1000000; i++)
	{
		auto s2 = str.substr(3);
	}
	time2 = clock();
	std::cout << static_cast<double>(time2 - time1) / CLOCKS_PER_SEC * 1000 << std::endl;

	//string_view����ָ����ʱ�ַ���
	std::string s{ "Hello" };
	std::string_view sv{ s + " World!" };
	std::cout << sv;

	return 0;
}