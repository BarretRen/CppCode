//智能指针如何做类型转换
#include <iostream>
#include <memory>

struct BaseClass {};

struct DerivedClass : BaseClass
{
	void f() const
	{
		std::cout << "Hello World!\n";
	}
	~DerivedClass() { // 注意：它不是虚的
		std::cout << "~DerivedClass\n";
	}
};

int main()
{
	std::shared_ptr<BaseClass> ptr_to_base(std::make_shared<DerivedClass>());

	//ptr_to_base->f(); // 错误不会编译： BaseClass 无名为 'f' 的成员

	std::static_pointer_cast<DerivedClass>(ptr_to_base)->f(); // OK
	// （构造临时 shared_ptr ，然后调用 operator-> ）

	static_cast<DerivedClass*>(ptr_to_base.get())->f(); // 亦 OK
	// （直接转型，不构造临时 shared_ptr ）
}