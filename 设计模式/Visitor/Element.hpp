#ifndef ELEMENT_HPP_INCLUDED
#define ELEMENT_HPP_INCLUDED

class Visitor;

class Element
{
public:
    virtual ~Element(){};
    virtual void accpet(Visitor* vis)=0;
protected:
    Element(){};
};

class ConcreteElementA:public Element
{
public:
    ConcreteElementA(){};
    ~ConcreteElementA(){};
    void accpet(Visitor* vis);
};

class ConcreteElementB:public Element
{
public:
    ConcreteElementB(){};
    ~ConcreteElementB(){};
    void accpet(Visitor* vis);
};
#endif // ELEMENT_HPP_INCLUDED
