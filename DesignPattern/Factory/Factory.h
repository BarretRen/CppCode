#ifndef FACTORY_HPP_INCLUDED
#define FACTORY_HPP_INCLUDED

class Product; //引用一个产品类

class Factory
{
public:
    ~Factory();
    virtual Product* createProduct()=0;

protected:
    Factory();
};

class SubFactory:public Factory
{
public:
    SubFactory();
    ~SubFactory();
    Product* createProduct();
};

#endif // FACTORY_HPP_INCLUDED
