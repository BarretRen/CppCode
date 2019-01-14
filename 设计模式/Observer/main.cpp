#include <iostream>
#include "Subject.hpp"
#include "Observer.hpp"
using namespace std;

int main()
{
    Subject* sub=new Subject();
    Observer* obv=new Observer();
    sub->Attach(obv);//注册观察者
    sub->setState("old");
    sub->notify();//通知观察者
    return 0;
}
