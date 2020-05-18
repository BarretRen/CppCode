/*
使用std::future保存异常并抛出
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

int main13()
{
    std::future<double> f = std::async(square_root, -1);
	try
	{
		//调用get()函数，如果没有问题，则返回函数值；如果存在异常，则future会抛出保存到异常，被下面的catch捕获到
		double y = f.get();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;//打印结果："x < 0"
	}
	return 0;
}