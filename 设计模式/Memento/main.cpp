#include <iostream>
#include "Originator.hpp"
#include "Memento.hpp"
using namespace std;

int main()
{
    Originator* o=new Originator();
    //����״̬
    o->setState("old");
    o->printState();
    //���ñ���¼
    Memento* men=o->createMemento();

    //������״̬
    o->setState("new");
    o->printState();

    //�ָ�״̬
    o->restoreToMemento(men);
    o->printState();

    return 0;
}
