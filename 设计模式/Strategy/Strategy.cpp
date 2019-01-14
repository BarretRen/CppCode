#include "Strategy.hpp"
#include <iostream>
using namespace std;



Strategy::~Strategy()
{
cout<<"~Strategy....."<<endl;
}

ConcreteStrategyA::~ConcreteStrategyA()
{
cout<<"~ConcreteStrategyA....."<<endl;
}
void ConcreteStrategyA::AlgrithmInterface()
{
cout<<"test ConcreteStrategyA....."<<endl;
}


ConcreteStrategyB::~ConcreteStrategyB()
{
cout<<"~ConcreteStrategyB....."<<endl;
}
void ConcreteStrategyB::AlgrithmInterface()
{
cout<<"test ConcreteStrategyB....."<<endl;
}
