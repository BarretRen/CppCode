#include "Flyweight.hpp"
#include <iostream>
using namespace std;

Flyweight::Flyweight(string state)
{
    _state=state;
}
Flyweight::~Flyweight(){}

void Flyweight::Operation(const string& state)
{

}
string Flyweight::getIntrinsicState()
{
    return _state;
}

SubFlyweight::SubFlyweight(string state):Flyweight(state)
{
    cout<<"SubFlyweight build "<<state<<endl;
}

void SubFlyweight::Operation(const string& state)
{
    cout<<"SubFlyweight: ÄÚº­["<<getIntrinsicState()<<"] Íâº­["<<state<<"]"<<endl;
}
