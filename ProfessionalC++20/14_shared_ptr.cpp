#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

int main()
{
    //创建shared pointer的三种方式
    //shared_ptr<string> p1(new string("nico"));
    shared_ptr<string> p1(new string("nico"), [](string* p) { //这种方式，可以自定义deleter
        cout << "delete " << *p << " in customer deleter" << endl;
        delete p;
        });
    shared_ptr<string> p2 = make_shared<string>("jutta");//推荐使用

    //C++20引入，自动按照默认值初始化
    shared_ptr<string> p3 = make_shared_for_overwrite<string>();//默认空字符串

    //填充vector
    vector<shared_ptr<string>> whoMadeCoffee;
    whoMadeCoffee.push_back(p2);
    whoMadeCoffee.push_back(p2);
    whoMadeCoffee.push_back(p1);
    whoMadeCoffee.push_back(p2);
    whoMadeCoffee.push_back(p1);
    whoMadeCoffee.push_back(p3);

    //打印vector
    for (auto vec : whoMadeCoffee)
    {
        cout << *vec << "  "; //vec是共享指针
    }
    cout << endl;

    //借助指针修改内容
    (*p1)[0] = 'N';
    p2->replace(0, 1, "J");

    //重新打印vector，内容被修改
    for (auto vec : whoMadeCoffee)
    {
        cout << *vec << "  ";
    }
    cout << endl;

    //打印指针的引用计数
    cout << "p1 count:" << p1.use_count() << endl; //打印3
    cout << "p2 count:" << p2.use_count() << endl; //打印4
    cout << "p2 count:" << p3.use_count() << endl; //打印2
    return 0;
}