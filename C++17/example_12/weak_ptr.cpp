#include <iostream>
#include <memory>
struct A;
struct B;

struct A{
	std::weak_ptr<B> p;
	~A()
	{
		std::cout<<"A deleted"<<std::endl;
	}
};

struct B{
	std::weak_ptr<A> p;
	~B()
	{
		std::cout<<"B deleted"<<std::endl;
	}
};

int main()
{
	auto a=std::make_shared<A>(); //A计数1
	auto b=std::make_shared<B>(); //B计数1
	a->p=b; //B计数为1，释放
	b->p=a; //A计数为1，释放

	return 0;
}