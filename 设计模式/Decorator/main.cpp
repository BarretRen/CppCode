#include <iostream>
#include "Decorator.hpp"
using namespace std;

int main()
{
    Component* com=new SubComponent();
    Decorator* dec=new Decorator(com);
    dec->Operation();

    delete dec;
    return 0;
}
