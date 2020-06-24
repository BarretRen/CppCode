#include <iostream>
#include "FlyweightFactory.hpp"
#include "Flyweight.hpp"
using namespace std;

int main()
{
    Factory* fact=new Factory();
    Flyweight* f1=fact->getFlyweight("hello");
    Flyweight* f2=fact->getFlyweight("world");
    Flyweight* f3=fact->getFlyweight("hello");

    return 0;
}
