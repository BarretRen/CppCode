#ifndef GRAPHTABLE_H
#define GRAPHTABLE_H
#include <list>
#include <iostream>

//图
template<typename T>
class Graph
{
public:
    Graph(const int num):n(num)
    {
        vertexList = new T*[n];
        headNodes = new std::list<int>[n];//一个节点对应一个链表
        nVerts = 0;
    }
    ~Graph()
    {
        delete [] vertexList;
        delete [] headNodes;
    }
    void addVertex(T* lab);
    void addEdge(int start, int end);
    void printNodes();
    void printLines();
private:
    T** vertexList; //保存所有节点的列表
    std::list<int>* headNodes;
    int n; //节点个数
    int nVerts; //计数用
};

template<typename T>
void Graph<T>::addVertex(T* lab)
{
    vertexList[nVerts++] = lab;
}

template<typename T>
void Graph<T>::addEdge(int start, int end)
{
    headNodes[start].push_back(end);
    headNodes[end].push_back(start);
}

template<typename T>
void Graph<T>::printNodes()
{
    for(int i=0; i<nVerts; i++)
        std::cout<<*vertexList[i]<<" ";
    std::cout<<std::endl;
}

template<typename T>
void Graph<T>::printLines()
{
    for(int i=0; i<nVerts; i++)
    {
        std::cout<<i<<"->";
        for(std::list<int>::iterator it=headNodes[i].begin(); it!=headNodes[i].end(); it++)
            std::cout<<*it<<"->";
        std::cout<<"end"<<std::endl;
    }
}
#endif // GRAPHTABLE_H
