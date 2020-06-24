#ifndef ABSTRACTIONIMP_HPP_INCLUDED
#define ABSTRACTIONIMP_HPP_INCLUDED

class AbstractionImp
{
public:
    virtual ~AbstractionImp();
    virtual void Operation()=0;
protected:
    AbstractionImp();
};

class SubAbstractionImpA:public AbstractionImp
{
public:
    SubAbstractionImpA();
    ~SubAbstractionImpA();
    virtual void Operation();
};

class SubAbstractionImpB:public AbstractionImp
{
public:
    SubAbstractionImpB();
    ~SubAbstractionImpB();
    virtual void Operation();
};
#endif // ABSTRACTIONIMP_HPP_INCLUDED
