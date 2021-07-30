//��ʾ�������η�������������Ȩ
//�Լ�return shared_ptr<T>(this)�������ü���ʧЧ������
#include <iostream>
#include <memory>
using namespace std;

class Foo : public enable_shared_from_this<Foo>
{
public:
    ~Foo()
    {
        cout << "Foo is deleted" << endl;
    }
    shared_ptr<Foo> getPointer()
    {
        // return shared_from_this(); //���ض�������Ȩ�Ĺ���ָ��
        return shared_ptr<Foo>(this); //���ع���ָ��,��������ָ�벻��������Ȩ
    }
};
int main()
{
    //������������ָ��
    auto ptr1{make_shared<Foo>()};
    auto ptr2{ptr1->getPointer()};
    //shared_from_this,����Ȩ���ü�����2
    //shared_ptr<Foo>(this),����Ȩ���ü�����1,�����ڴ��ظ��ͷ�
    cout << ptr1.use_count() << endl;
    cout << ptr2.use_count() << endl;
}