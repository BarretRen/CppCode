#include <iostream>
#include "Context.hpp"
using namespace std;

int main()
{
    Strategy* ps;
    ps = new ConcreteStrategyA();
    Context* pc = new Context(ps);
    pc->doAction();
    if (NULL != pc)
        delete pc;
    return 0;
}
