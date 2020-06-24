#include "Handle.hpp"
#include <iostream>
using namespace std;

void ConcreteHandleA::handleRequest()
{
    if(getSuccessor() != 0)
    {
        cout<<"ConcreteHandleA,将操作传递给后继对象处理..."<<endl;
        getSuccessor()->handleRequest();
    }
    else
    {
        cout<<"ConcreteHandleA,没有后继对象处理，自己处理..."<<endl;
    }
}

void ConcreteHandleB::handleRequest()
{
    if(getSuccessor() != 0)
    {
        cout<<"ConcreteHandleB 将操作传递给后继对象处理..."<<endl;
        getSuccessor()->handleRequest();
    }
    else
    {
        cout<<"ConcreteHandleB 没有后继对象处理，自己处理..."<<endl;
    }
}
