#include <iostream>
#include "Subject.hpp"
#include "Observer.hpp"
using namespace std;

int main()
{
    Subject* sub=new Subject();
    Observer* obv=new Observer();
    sub->Attach(obv);//ע��۲���
    sub->setState("old");
    sub->notify();//֪ͨ�۲���
    return 0;
}
