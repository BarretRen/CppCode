//����ָ�����������ת��
#include <iostream>
#include <memory>

struct BaseClass {};

struct DerivedClass : BaseClass
{
	void f() const
	{
		std::cout << "Hello World!\n";
	}
	~DerivedClass() { // ע�⣺���������
		std::cout << "~DerivedClass\n";
	}
};

int main()
{
	std::shared_ptr<BaseClass> ptr_to_base(std::make_shared<DerivedClass>());

	//ptr_to_base->f(); // ���󲻻���룺 BaseClass ����Ϊ 'f' �ĳ�Ա

	std::static_pointer_cast<DerivedClass>(ptr_to_base)->f(); // OK
	// ��������ʱ shared_ptr ��Ȼ����� operator-> ��

	static_cast<DerivedClass*>(ptr_to_base.get())->f(); // �� OK
	// ��ֱ��ת�ͣ���������ʱ shared_ptr ��
}