#include "Template.hpp"
#include <iostream>
using namespace std;


void AbstractClass::templateMethod()
{
    operation1();
    operation2();
}

void SubAbstractClass1::operation1()
{
    cout<<"SubAbstractClass1::operation1()"<<endl;
}
void SubAbstractClass1::operation2()
{
    cout<<"SubAbstractClass1::operation2()"<<endl;
}


void SubAbstractClass2::operation1()
{
    cout<<"SubAbstractClass2::operation1()"<<endl;
}
void SubAbstractClass2::operation2()
{
    cout<<"SubAbstractClass2::operation2()"<<endl;
}
