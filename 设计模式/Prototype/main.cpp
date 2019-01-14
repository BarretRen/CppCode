#include <iostream>
#include "Prototype.hpp"
using namespace std;

int main()
{
    Prototype* p=new SubPrototype();
    Prototype* p2=p->clone();

    if(p==p2)
        cout<<"the same object"<<endl;
    else
        cout<<"the different object"<<endl;

    return 0;
}
