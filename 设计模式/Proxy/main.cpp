#include <iostream>
#include "Proxy.hpp"
using namespace std;

int main()
{
    Subject* sub = new SubSubject();
    Proxy* p = new Proxy(sub);
    p->request();
    return 0;
}
