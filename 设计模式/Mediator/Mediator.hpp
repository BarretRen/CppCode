#ifndef MEDIATOR_HPP_INCLUDED
#define MEDIATOR_HPP_INCLUDED
#include "Colleage.hpp"

class Mediator
{
public:
    Mediator(){};
    ~Mediator(){};
    void doActionFromAtoB();
    void doActionFromBtoA();
    void setColleage(Colleage* a, Colleage* b);
private:
    Colleage* _a;
    Colleage* _b;
};
#endif // MEDIATOR_HPP_INCLUDED
