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

//��������ͨ����ϵķ�ʽ����µķ���
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
