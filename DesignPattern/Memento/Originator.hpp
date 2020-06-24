#ifndef ORIGINATOR_HPP_INCLUDED
#define ORIGINATOR_HPP_INCLUDED
#include <string>
#include "Memento.hpp"
using namespace std;

class Originator
{
public:
    Originator();
    Originator(const string& str);
    ~Originator(){};
    Memento* createMemento();
    void restoreToMemento(Memento* mt);
    string getState()
    {
        return _str;
    };
    void setState(const string& str)
    {
        _str=str;
    };
    void printState();
private:
    string _str;
};

#endif // ORIGINATOR_HPP_INCLUDED
