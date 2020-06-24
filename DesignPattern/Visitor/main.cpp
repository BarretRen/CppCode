#include <iostream>
#include "Element.hpp"
#include "Visitor.hpp"
using namespace std;

int main()
{
    Visitor* v=new SubVisitorA();
    Element* e=new ConcreteElementA();
    e->accpet(v);
    return 0;
}
