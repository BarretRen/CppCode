#ifndef FACADE_HPP_INCLUDED
#define FACADE_HPP_INCLUDED

class Subsystem1
{
public:
    void Operation();
};

class Subsystem2
{
public:
    void Operation();
};

class Facade
{
public:
    Facade();
    ~Facade();
    void operationWrapper();
private:
    Subsystem1* _sub1;
    Subsystem2* _sub2;
};
#endif // FACADE_HPP_INCLUDED
