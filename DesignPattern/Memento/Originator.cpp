#include "Originator.hpp"
#include <iostream>

Originator::Originator()
{
    _str='\0';
}

Originator::Originator(const string& str)
{
    _str=str;
}

Memento* Originator::createMemento()
{
    return new Memento(_str);
}

void Originator::restoreToMemento(Memento* men)
{
    _str=men->getState();
}

void Originator::printState()
{
    cout<<"now state is "<<_str<<endl;
}
