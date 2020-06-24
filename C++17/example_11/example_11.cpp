#include <iostream>
#include <tuple>
#include <string>

int main()
{
	auto t = std::make_tuple(3.8, "A", "Barret Ren");
	//get获取元素
	std::cout<<std::get<0>(t)<<std::endl;
	std::cout<<std::get<1>(t)<<std::endl;
	std::cout<<std::get<2>(t)<<std::endl;

	//tie进行拆包
	double a;
	std::string b;
	std::string c;
	std::tie(a, b, c)=t;
	std::cout<<c<<std::endl;
}