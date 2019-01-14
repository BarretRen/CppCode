#include "FlyweightFactory.hpp"
#include <iostream>
#include <cassert>
using namespace std;

Flyweight* Factory::getFlyweight(const string& key)
{
    vector<Flyweight*>::iterator it=_fly.begin();
    for(;it!=_fly.end();it++)
    {
        //����ҵ�key��Ӧ�Ķ���
        if((*it)->getIntrinsicState()==key)
        {
            cout<<"already create the object by user"<<endl;
            return *it;
        }

    }
    Flyweight* fn=new SubFlyweight(key);
    _fly.push_back(fn);
    return fn;
}
