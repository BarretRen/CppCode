//演示类对象如何返回自身共享所有权
//以及return shared_ptr<T>(this)导致引用计数失效的问题
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
        // return shared_from_this(); //返回对象所有权的共享指针
        return shared_ptr<Foo>(this); //返回共享指针,但跟其他指针不共享所有权
    }
};
int main()
{
    //创建两个智能指针
    auto ptr1{make_shared<Foo>()};
    auto ptr2{ptr1->getPointer()};
    //shared_from_this,所有权引用计数是2
    //shared_ptr<Foo>(this),所有权引用计数是1,导致内存重复释放
    cout << ptr1.use_count() << endl;
    cout << ptr2.use_count() << endl;
}