#ifndef COMPONENT_HPP_INCLUDED
#define COMPONENT_HPP_INCLUDED

class Component
{
public:
    Component(){};
    virtual ~Component(){};
    virtual void Operation()=0;
    virtual void add(const Component*){};
    virtual void Remove(const Component*){};
    virtual Component* getChild(int){return 0;};
};

#endif // COMPONENT_HPP_INCLUDED
