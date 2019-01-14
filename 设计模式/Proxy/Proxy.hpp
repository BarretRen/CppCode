#ifndef PROXY_HPP_INCLUDED
#define PROXY_HPP_INCLUDED

class Subject
{
public:
    virtual ~Subject(){};
    virtual void Request()=0;
protected:
    Subject(){};
};

class SubSubject:public Subject
{
public:
    SubSubject(){};
    ~SubSubject(){};
    void Request();
};

class Proxy
{
public:
    Proxy(){};
    Proxy(Subject* sub);
    ~Proxy();
    void request();
private:
    Subject* _sub;
};
#endif // PROXY_HPP_INCLUDED
