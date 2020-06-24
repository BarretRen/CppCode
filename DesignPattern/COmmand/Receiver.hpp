#ifndef RECEIVER_HPP_INCLUDED
#define RECEIVER_HPP_INCLUDED
#include <iostream>
using namespace std;

class Receiver
{
public:
    Receiver(){};
    ~Receiver(){};
    void action()
    {
        cout<<"received the action..."<<endl;
    };
};
#endif // RECEIVER_HPP_INCLUDED
