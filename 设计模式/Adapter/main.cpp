#include <iostream>
#include "Adapter.hpp"
using namespace std;

int main()
{
    Adaptee* ade=new Adaptee();
    Target* adt=new Adapter(ade);
    adt->Request();
    return 0;
}
