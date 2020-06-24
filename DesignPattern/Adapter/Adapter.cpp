#include "Adapter.hpp"
#include <iostream>
using namespace std;

Target::Target(){}
Target::~Target(){}
void Target::Request()
{
    cout<<"target::request"<<endl;
}

Adaptee::Adaptee(){}
Adaptee::~Adaptee(){}
void Adaptee::SpecificRequest()
{
    cout<<"Adaptee::SpecificRequest"<<endl;
}

Adapter::Adapter(Adaptee* ade)
{
    _ade=ade;
}
Adapter::~Adapter(){}
void Adapter::Request()
{
    _ade->SpecificRequest();
}
