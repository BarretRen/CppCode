#include "Element.hpp"
#include "Visitor.hpp"
#include <iostream>
using namespace std;

void SubVisitorA::visitElementA(Element* ele)
{
    cout<<"SubVisitorA I will visit Element A..."<<endl;
}
void SubVisitorA::visitElementB(Element* ele)
{
    cout<<"SubVisitorA I will visit Element B..."<<endl;
}

void SubVisitorB::visitElementA(Element* ele)
{
    cout<<"SubVisitorB I will visit Element A..."<<endl;
}
void SubVisitorB::visitElementB(Element* ele)
{
    cout<<"SubVisitorB I will visit Element B..."<<endl;
}
