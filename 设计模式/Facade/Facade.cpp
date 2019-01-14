#include "Facade.hpp"
#include <iostream>
using namespace std;

void Subsystem1::Operation()
{
    cout<<"systerm 1 operation"<<endl;
}

void Subsystem2::Operation()
{
    cout<<"systerm 2 operation"<<endl;
}

Facade::Facade()
{
    _sub1=new Subsystem1();
    _sub2=new Subsystem2();
}

Facade::~Facade()
{
    delete _sub1;
    delete _sub2;
}

void Facade::operationWrapper()
{
    _sub1->Operation();
    _sub2->Operation();
}
