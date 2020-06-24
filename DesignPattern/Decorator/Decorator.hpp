#ifndef DECORATOR_HPP_INCLUDED
#define DECORATOR_HPP_INCLUDED

class Component
{
public:
    virtual ~Component(){};
    virtual void Operation();
};

class SubComponent:public Component
{
public:
    void Operation();
};

//修饰器，通过组合的方式添加新的方法
class Decorator:public Component
{
public:
    Decorator(Component* com);
    virtual ~Decorator();
    void Operation();
    void addNewOperation();
private:
    Component* _com;
};
#endif // DECORATOR_HPP_INCLUDED
