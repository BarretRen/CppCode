#include "Proxy.hpp"
#include <iostream>
using namespace std;

void SubSubject::Request()
{
    cout<<"SubSubject request..."<<endl;
}

Proxy::Proxy(Subject* sub)
{
    _sub=sub;
}

Proxy::~Proxy()
{
    delete _sub;
}

void Proxy::request()
{
    cout<<"Proxy request..."<<endl;
    _sub->Request();
}
