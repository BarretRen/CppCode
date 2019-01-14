#ifndef FLYWEIGHT_HPP_INCLUDED
#define FLYWEIGHT_HPP_INCLUDED
#include <string>
using namespace std;

class Flyweight
{
public:
    virtual ~Flyweight();
    virtual void Operation(const string& state);
    string getIntrinsicState();
protected:
    Flyweight(string state);
private:
    string _state;
};

class SubFlyweight:public Flyweight
{
public:
    SubFlyweight(string state);
    ~SubFlyweight(){};
    void Operation(const string& state);
};
#endif // FLYWEIGHT_HPP_INCLUDED
