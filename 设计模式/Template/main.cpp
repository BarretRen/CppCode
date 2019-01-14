#include <iostream>
#include "Template.hpp"
using namespace std;

int main()
{
    AbstractClass* p1=new SubAbstractClass1();
    AbstractClass* p2=new SubAbstractClass2();

    p1->templateMethod();
    p2->templateMethod();

    return 0;
}
