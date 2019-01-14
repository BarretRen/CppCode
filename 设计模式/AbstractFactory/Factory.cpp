#include "Factory.hpp"
#include "Product.hpp"
#include <iostream>
using namespace std;

AbstractFactory::AbstractFactory()
{

}
AbstractFactory::~AbstractFactory()
{

}
//����1������ƷA1��B1
SubFactory1::SubFactory1()
{

}
SubFactory1::~SubFactory1()
{

}
AbstractProductA* SubFactory1::createProductA()
{
    return new ProductA1();
}
AbstractProductB* SubFactory1::createProductB()
{
    return new ProductB1();
}
//����2������ƷA2��B2
SubFactory2::SubFactory2()
{

}
SubFactory2::~SubFactory2()
{

}
AbstractProductA* SubFactory2::createProductA()
{
    return new ProductA2();
}
AbstractProductB* SubFactory2::createProductB()
{
    return new ProductB2();
}
