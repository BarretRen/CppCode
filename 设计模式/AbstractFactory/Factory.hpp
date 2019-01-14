#ifndef ABSTRACTFACTORY_HPP_INCLUDED
#define ABSTRACTFACTORY_HPP_INCLUDED

class AbstractProductA;
class AbstractProductB;

class AbstractFactory
{
public:
    virtual ~AbstractFactory();
    virtual AbstractProductA* createProductA()=0;
    virtual AbstractProductB* createProductB()=0;
protected:
    AbstractFactory();
};

class SubFactory1:public AbstractFactory
{
public:
    SubFactory1();
    ~SubFactory1();
    AbstractProductA* createProductA();
    AbstractProductB* createProductB();
};

class SubFactory2:public AbstractFactory
{
public:
    SubFactory2();
    ~SubFactory2();
    AbstractProductA* createProductA();
    AbstractProductB* createProductB();
};


#endif // ABSTRACTFACTORY_HPP_INCLUDED
