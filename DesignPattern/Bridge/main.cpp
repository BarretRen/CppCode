#include <iostream>
#include "Abstraction.hpp"
#include "AbstractionImp.hpp"
using namespace std;

int main()
{
    AbstractionImp* imp=new SubAbstractionImpA();
    Abstraction* abs=new RefinedAbstraction(imp);

    abs->Operation();
    return 0;
}
