#ifndef FLYWEIGHTFACTORY_HPP_INCLUDED
#define FLYWEIGHTFACTORY_HPP_INCLUDED
#include "Flyweight.hpp"
#include <string>
#include <vector>
using namespace std;

class Factory
{
public:
    Flyweight* getFlyweight(const string& key);
private:
    vector<Flyweight*> _fly;
};


#endif // FLYWEIGHTFACTORY_HPP_INCLUDED
