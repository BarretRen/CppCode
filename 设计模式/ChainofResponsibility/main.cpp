#include <iostream>
#include "Handle.hpp"
using namespace std;

int main()
{
    Handle* h1=new ConcreteHandleA();
    Handle* h2=new ConcreteHandleB();
    //����h1�ĺ�̶���Ϊh2
    h1->setSuccessor(h2);

    h1->handleRequest();
    return 0;
}
