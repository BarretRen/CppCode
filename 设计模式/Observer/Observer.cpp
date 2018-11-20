#include "Observer.hpp"
#include <iostream>

Observer::Observer()
{
    _st='\0';
}

Observer::~Observer()
{
}

void Observer::printInfo()
{
    cout<<"Observer......"<<endl;
}

void Observer::update(State st)
{
    _st=st;
    printInfo();
}
