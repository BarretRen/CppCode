#include "Decorator.hpp"
#include <iostream>
using namespace std;

void Component::Operation()
{
    cout<<"Component::Operation"<<endl;
}
void SubComponent::Operation()
{
    cout<<"SubComponent::Operation"<<endl;
}

Decorator::Decorator(Component* com)
{
    _com=com;
}
Decorator::~Decorator()
{
    delete _com;
}
void Decorator::Operation()
{
    cout<<"Decorator::Operation"<<endl;
    _com->Operation();
    addNewOperation();
}
void Decorator::addNewOperation()
{
    cout<<"Decorator::addNewOperation"<<endl;
}
