#include <iostream>
#include "Originator.hpp"
#include "Memento.hpp"
using namespace std;

int main()
{
    Originator* o=new Originator();
    //ÉèÖÃ×´Ì¬
    o->setState("old");
    o->printState();
    //ÉèÖÃ±¸ÍüÂ¼
    Memento* men=o->createMemento();

    //ÉèÖÃÐÂ×´Ì¬
    o->setState("new");
    o->printState();

    //»Ö¸´×´Ì¬
    o->restoreToMemento(men);
    o->printState();

    return 0;
}
