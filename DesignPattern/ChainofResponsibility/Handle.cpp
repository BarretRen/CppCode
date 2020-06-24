#include "Handle.hpp"
#include <iostream>
using namespace std;

void ConcreteHandleA::handleRequest()
{
    if(getSuccessor() != 0)
    {
        cout<<"ConcreteHandleA,���������ݸ���̶�����..."<<endl;
        getSuccessor()->handleRequest();
    }
    else
    {
        cout<<"ConcreteHandleA,û�к�̶������Լ�����..."<<endl;
    }
}

void ConcreteHandleB::handleRequest()
{
    if(getSuccessor() != 0)
    {
        cout<<"ConcreteHandleB ���������ݸ���̶�����..."<<endl;
        getSuccessor()->handleRequest();
    }
    else
    {
        cout<<"ConcreteHandleB û�к�̶������Լ�����..."<<endl;
    }
}
