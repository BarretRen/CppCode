/*
ʹ��std::future�����쳣���׳�
*/

#include <iostream>
#include <future>

double square_root(double x)
{
    if (x < 0)
    {
        throw std::out_of_range("x < 0");
    }
    return sqrt(x);
}

int main()
{
    std::future<double> f = std::async(square_root, -1);
	try
	{
		//����get()���������û�����⣬�򷵻غ���ֵ����������쳣����future���׳����浽�쳣���������catch����
		double y = f.get();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;//��ӡ�����"x < 0"
	}
	return 0;
}