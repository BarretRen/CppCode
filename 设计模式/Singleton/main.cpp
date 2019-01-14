#include <iostream>
#include "Singleton.hpp"
using namespace std;

int main()
{
    Singleton* s1=Singleton::getInstance();
    Singleton* s2=Singleton::getInstance();

    if(s1==s2)
        cout<<"the same object"<<endl;
    else
        cout<<"the different object"<<endl;
    return 0;
}
