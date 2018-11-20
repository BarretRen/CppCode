#ifndef COLLEAGE_HPP_INCLUDED
#define COLLEAGE_HPP_INCLUDED
#include <string>
#include <iostream>
using namespace std;

class Mediator;

class Colleage
{
public:
    Colleage(Mediator* md);
    virtual ~Colleage(){};
    virtual void action()=0;
    void setState(const string& str)
    {
        _str=str;
    };
    string getState()
    {
        return _str;
    };
protected:

    string _str;
    Mediator* _md;
};

class SubColleageA: public Colleage
{
public:
    SubColleageA(Mediator* md):Colleage(md){};
    void action();
};

class SubColleageB: public Colleage
{
public:
    SubColleageB(Mediator* md):Colleage(md){};
    void action();
};
#endif // COLLEAGE_HPP_INCLUDED
