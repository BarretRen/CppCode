#include <iostream>
#include "Receiver.hpp"
#include "Command.hpp"
using namespace std;

int main()
{
    Receiver* r=new Receiver();
    Command* cmd=new Command(r);
    cmd->execute();

    Command* cmd2=new Command(r,&Receiver::action);
    cmd2->execute2();
    return 0;
}
