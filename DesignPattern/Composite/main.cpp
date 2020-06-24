#include <iostream>
#include "Composite.hpp"
#include "Leaf.hpp"
using namespace std;

int main()
{
    Leaf* leaf=new Leaf();
    leaf->Operation();

    Composite* com=new Composite();
    com->add(leaf);
    com->Operation();

    Component* l=com->getChild(0);
    l->Operation();
    return 0;
}
