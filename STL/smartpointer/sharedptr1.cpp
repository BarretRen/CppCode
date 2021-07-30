//共享智能指针的基本使用
#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

int main()
{
    //创建shared pointer的两种方式
    // shared_ptr<string> p1(new string("nico"));
    shared_ptr<string> p1(new string("nico"), [](string *p) { //这种方式，可以自定义deleter
        cout << "delete " << *p << " in customer deleter" << endl;
        delete p;
    });
    shared_ptr<string> p2 = make_shared<string>("jutta"); //推荐使用

    //填充vector
    vector<shared_ptr<string>> whoMadeCoffee;
    whoMadeCoffee.push_back(p2);
    whoMadeCoffee.push_back(p2);
    whoMadeCoffee.push_back(p1);
    whoMadeCoffee.push_back(p2);
    whoMadeCoffee.push_back(p1);

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
    return 0;
}