#include <iostream>
#include "graphtable.h"

using namespace std;

int main()
{
    Graph<char> g(5);
    char a='A';
    char b='B';
    char c='C';
    char d='D';
    char e='E';

    g.addVertex(&a);
    g.addVertex(&b);
    g.addVertex(&c);
    g.addVertex(&d);
    g.addVertex(&e);

    g.addEdge(0,1);
    g.addEdge(0,3);
    g.addEdge(1,4);
    g.addEdge(3,4);
    g.addEdge(2,4);

    g.printNodes();
    g.printLines();

    return 0;
}
