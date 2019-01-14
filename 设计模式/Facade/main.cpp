#include <iostream>
#include "Facade.hpp"
using namespace std;

int main()
{
    Facade* f=new Facade();
    f->operationWrapper();
    return 0;
}
