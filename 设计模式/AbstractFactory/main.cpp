#include <iostream>
#include "Factory.hpp"
#include "Product.hpp"
using namespace std;

int main()
{
    AbstractFactory* f1=new SubFactory1();
    f1->createProductA();
    f1->createProductB();

    AbstractFactory* f2=new SubFactory2();
    f2->createProductA();
    f2->createProductB();

    return 0;
}
