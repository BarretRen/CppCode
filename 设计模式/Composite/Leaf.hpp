#ifndef LEAF_HPP_INCLUDED
#define LEAF_HPP_INCLUDED
#include <iostream>
#include "Component.hpp"
using namespace std;

class Leaf:public Component
{
public:
    void Operation()
    {
        cout<<"Leaf operation..."<<endl;
    };
};

#endif // LEAF_HPP_INCLUDED
