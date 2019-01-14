#ifndef TEMPLATE_HPP_INCLUDED
#define TEMPLATE_HPP_INCLUDED

class AbstractClass
{
public:
    virtual ~AbstractClass(){};
    void templateMethod();
protected:
    virtual void operation1()=0;
    virtual void operation2()=0;
    AbstractClass(){};
};

class SubAbstractClass1: public AbstractClass
{
public:
    SubAbstractClass1(){};
    ~SubAbstractClass1(){};
protected:
    void operation1();
    void operation2();

};

class SubAbstractClass2: public AbstractClass
{
public:
    SubAbstractClass2(){};
    ~SubAbstractClass2(){};
protected:
    void operation1();
    void operation2();

};
#endif // TEMPLATE_HPP_INCLUDED
