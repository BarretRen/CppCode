#include "Element.hpp"
#include "Visitor.hpp"
#include <iostream>
using namespace std;

void ConcreteElementA::accpet(Visitor* vis)
{
    vis->visitElementA(this);
    cout<<"visiting element A..."<<endl;
}

void ConcreteElementB::accpet(Visitor* vis)
{
    vis->visitElementB(this);
    cout<<"visiting element B..."<<endl;
}
