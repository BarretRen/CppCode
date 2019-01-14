#include "Prototype.hpp"
#include <iostream>
using namespace std;

Prototype::Prototype()
{

}
Prototype::~Prototype()
{

}
Prototype* Prototype::clone() const
{
    return 0;
}

SubPrototype::SubPrototype()
{

}
SubPrototype::~SubPrototype()
{

}
SubPrototype::SubPrototype(const SubPrototype& sp)
{
    cout<<"¿½±´¹¹Ôìº¯Êý"<<endl;
}

Prototype* SubPrototype::clone() const
{
    return new SubPrototype(*this);
}
