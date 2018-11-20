#include <iostream>
#include "Mediator.hpp"
#include "Colleage.hpp"

using namespace std;

int main()
{
    Mediator* media=new Mediator();
    Colleage* a=new SubColleageA(media);
    Colleage* b=new SubColleageB(media);
    media->setColleage(a,b);

    a->setState("Old");
    b->setState("new");
    a->action();
    b->action();


    return 0;
}
