#ifndef ADAPTER_HPP_INCLUDED
#define ADAPTER_HPP_INCLUDED

class Target
{
public:
    Target();
    virtual ~Target();
    virtual void Request();
};

class Adaptee
{
public:
    Adaptee();
    ~Adaptee();
    void SpecificRequest();
};

class Adapter:public Target
{
public:
    Adapter(Adaptee* ade);
    ~Adapter();
    void Request();
private:
    Adaptee*_ade;
};

#endif // ADAPTER_HPP_INCLUDED
