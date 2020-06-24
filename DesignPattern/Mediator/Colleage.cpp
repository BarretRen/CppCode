#include "Colleage.hpp"
#include "Mediator.hpp"
Colleage::Colleage(Mediator* md)
{
    _md=md;
}

void SubColleageA::action()
{
    _md->doActionFromAtoB();
    cout<<"state of A: "<<getState()<<endl;
}

void SubColleageB::action()
{
    _md->doActionFromBtoA();
    cout<<"state of B: "<<getState()<<endl;
};
