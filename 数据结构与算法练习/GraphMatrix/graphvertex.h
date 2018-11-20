/*
    邻接矩阵表示图
    失实现深度优先搜索
*/
#ifndef GRAPHVERTEX_H
#define GRAPHVERTEX_H
#include <iostream>
#include <stack>
#include <queue>

using namespace std;
//节点
class Vertex
{
public:
    Vertex(char lab):lab(lab)
    {
        isVisited = false;
    }


    char lab;
    bool isVisited;
};

//图
class Graph
{
public:
    Graph();
    ~Graph();
    void addVertex(char lab);
    void addEdge(int start, int end);
    void printMatrix();
    void showVertex(int index);
    void DFS();//深度优先搜索函数
    void BFS();//广度优先搜索函数
private:
    Vertex* list[20]; //保存图的每个节点
    int num; //节点个数
    int Mat[20][20]; //邻接矩阵

    int getNextUnVisitedVertex(int index);
};

Graph::Graph()
{
    num = 0;
    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 20; j++)
            Mat[i][j] = 0;
}

Graph::~Graph()
{
    for (int i = 0; i < num; i++)
        delete list[i];
}

void Graph::addVertex(char lab)
{
    list[num++] = new Vertex(lab);
}

void Graph::addEdge(int start, int end)
{
    //对称，A-B和B-A都要置1
    Mat[start][end] = 1;
    Mat[end][start] = 1;
}

void Graph::printMatrix()
{
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < num; j++)
            std::cout<<Mat[i][j]<<" ";
        std::cout<<std::endl;
    }
}

void Graph::showVertex(int index)
{
    //v为节点下标
    std::cout<<list[index]->lab<<" ";
}

int Graph::getNextUnVisitedVertex(int index)
{
    for (int i=0; i<num; i++)
    {
        if(Mat[index][i] == 1 && list[i]->isVisited == false)
            return i;
    }
    return -1;
}

void Graph::DFS()
{
    stack<int> gStack;//栈用来保存节点的index
    //从0个节点开始显示
    list[0]->isVisited = true;
    showVertex(0);
    gStack.push(0);//将访问过的节点放入栈

    int index;
    while (gStack.size() > 0)
    {
        index = getNextUnVisitedVertex(gStack.top());
        if (index == -1)
        {
            gStack.pop();//往回返一个节点，删除当前
        }
        else
        {
            list[index]->isVisited = true;
            showVertex(index);
            gStack.push(index);
        }
    }

    for(int i=0; i<num; i++)
        list[i]->isVisited = false;//还原记得状态

}

void Graph::BFS()
{
    queue<int> gQueue;//保存访问过的节点index
    //从0个节点开始显示
    list[0]->isVisited = true;
    showVertex(0);
    gQueue.push(0);//将访问过的节点放入栈

    int index;
    while (gQueue.size() > 0)
    {
        index = getNextUnVisitedVertex(gQueue.front());
        while (index != -1)
        {
            //找出当前节点所有关联节点，放入队列
            list[index]->isVisited = true;
            showVertex(index);
            gQueue.push(index);
            index = getNextUnVisitedVertex(gQueue.front());
        }

        gQueue.pop();//删除当前节点，因为已经show
    }

    for(int i=0; i<num; i++)
        list[i]->isVisited = false;//还原记得状态
}
#endif // GRAPHVERTEX_H
