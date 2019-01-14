#ifndef SUBJECT_HPP_INCLUDED
#define SUBJECT_HPP_INCLUDED
#include <list>
#include <string>
using namespace std;

typedef string State;

class Observer;
class Subject
{
public:
    virtual ~Subject(){};
    virtual void Attach(Observer* obv);
    virtual void detach(Observer* obv);
    virtual void notify();
    virtual void setState(const State& st);
    virtual State getState();
    Subject();
private:
    list<Observer*>* _obvs;
    State _st;
};

#endif // SUBJECT_HPP_INCLUDED
