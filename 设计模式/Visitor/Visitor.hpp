#ifndef VISITOR_HPP_INCLUDED
#define VISITOR_HPP_INCLUDED

class ConcreteElementA;
class ConcreteElementB;
class Element;

class Visitor
{
public:
    ~Visitor(){};
    virtual void visitElementA(Element*)=0;
    virtual void visitElementB(Element*)=0;
protected:
    Visitor(){};
};

class SubVisitorA:public Visitor
{
public:
    SubVisitorA(){};
    ~SubVisitorA(){};
    void visitElementA(Element*);
    void visitElementB(Element*);
};

class SubVisitorB:public Visitor
{
public:
    SubVisitorB(){};
    ~SubVisitorB(){};
    void visitElementA(Element*);
    void visitElementB(Element*);
};
#endif // VISITOR_HPP_INCLUDED
