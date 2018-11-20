#ifndef COMPOSITE_HPP_INCLUDED
#define COMPOSITE_HPP_INCLUDED
#include "Component.hpp"
#include <vector>
using namespace std;

class Composite:public Component
{
public:
    void Operation();
    void add(Component* com);
    void Remove(Component* com);
    Component* getChild(int index);
private:
    vector<Component*> vec;
};


#endif // COMPOSITE_HPP_INCLUDED
