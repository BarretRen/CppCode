/*
 * 图的邻接矩阵表示
 */
#include <iostream>
#include "graphvertex.h"

using namespace std;

int main()
{
    Graph g;
    g.addVertex('A');
    g.addVertex('B');
    g.addVertex('C');
    g.addVertex('D');
    g.addVertex('E');

    g.addEdge(0, 1);//A-B
    g.addEdge(0, 3);//A-D
    g.addEdge(1, 4);//
    g.addEdge(3, 4);
    g.addEdge(2, 4);

    g.printMatrix();

    cout<<endl<<"DFS result:"<<endl;
    g.DFS();

    cout<<endl<<"BFS result:"<<endl;
    g.BFS();

    return 0;
}
