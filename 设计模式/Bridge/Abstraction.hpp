#ifndef ABSTRACTION_HPP_INCLUDED
#define ABSTRACTION_HPP_INCLUDED
#include "AbstractionImp.hpp"

class Abstraction
{
public:
    virtual ~Abstraction();
    virtual void Operation()=0;
protected:
    Abstraction();
};

class RefinedAbstraction:public Abstraction
{
public:
    RefinedAbstraction(AbstractionImp* imp);
    ~RefinedAbstraction();
    void Operation();
private:
    AbstractionImp* _imp;
};
#endif // ABSTRACTION_HPP_INCLUDED
