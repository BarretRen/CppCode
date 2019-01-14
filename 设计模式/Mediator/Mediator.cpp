#include "Mediator.hpp"

void Mediator::doActionFromAtoB()
{
    _b->setState(_a->getState());
}

void Mediator::doActionFromBtoA()
{
    _a->setState(_b->getState());
}
void Mediator::setColleage(Colleage* a, Colleage* b)
{
    _a=a;
    _b=b;
}
