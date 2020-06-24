#ifndef MEMENTO_HPP_INCLUDED
#define MEMENTO_HPP_INCLUDED
#include "Originator.hpp"
#include <string>
using namespace std;

class Memento
{
private:
    string _str;
    //��Originator����Ϊ��Ԫ�࣬���Է���Memento���캯��
    friend class Originator;
    Memento(){};
    Memento(const string& str)
    {
        _str=str;
    };
    ~Memento(){};
    void setState(const string& str)
    {
        _str=str;
    };
    string getState()
    {
        return _str;
    };
};
#endif // MEMENTO_HPP_INCLUDED
