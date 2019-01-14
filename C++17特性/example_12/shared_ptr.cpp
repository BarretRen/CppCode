/*
* shared_ptr智能指针
*/
#include <iostream>
#include <memory>

int main()
{
	std::shared_ptr<int> share_ptr = std::make_shared<int>(10); //创建int指针，指向10常量
	std::cout<<*share_ptr<<std::endl;

	(*share_ptr)++;
	std::cout<<*share_ptr<<std::endl;

	auto p2=share_ptr; //计数加一
	auto p3=share_ptr; //计数加一
	auto p4=share_ptr.get(); //get用于获取原始指针，计数不变
	std::cout<<share_ptr.use_count()<<std::endl;

	p2.reset(); //reset用于减少一个计数，同时p2不可用
	std::cout<<share_ptr.use_count()<<std::endl;
	std::cout<<(p2 == nullptr)<<std::endl;
	//离开作用域，指针自动释放
	return 0;
}