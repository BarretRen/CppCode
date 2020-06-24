#include "Subject.hpp"
#include "Observer.hpp"

Subject::Subject()
{
    _obvs=new list<Observer*>;
    _st='\0';
}

void Subject::Attach(Observer* obv)
{
    _obvs->push_front(obv);
}

void Subject::detach(Observer* obv)
{
    if(obv != 0)
        _obvs->remove(obv);
}

void Subject::notify()
{
    //通知每一个观察者
    list<Observer*>::iterator it=_obvs->begin();
    for(;it != _obvs->end();it++)
        (*it)->update(_st);
}

void Subject::setState(const State& st)
{
    _st=st;
}

State Subject::getState()
{
    return _st;
}
