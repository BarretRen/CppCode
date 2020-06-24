#include <iostream>
#include "bst.h"

using namespace std;

int main()
{
    BST<int> binaryTree;
    Element<int> a,b,c,d,e,f,g,h,i,j;
    a.key = 5;
    b.key = 3;
    c.key = 11;
    d.key = 3;
    e.key = 15;
    f.key = 2;
    g.key = 8;
    h.key = 22;
    i.key = 20;
    j.key = 9;

    cout<<"\n"<<binaryTree.insertKey(a); //a = 5,是root
    cout<<"\n"<<binaryTree.insertKey(b);
    cout<<"\n"<<binaryTree.insertKey(c);
    cout<<"\n"<<binaryTree.insertKey(d);
    cout<<"\n"<<binaryTree.insertKey(e);
    cout<<"\n"<<binaryTree.insertKey(f);
    cout<<"\n"<<binaryTree.insertKey(g);
    cout<<"\n"<<binaryTree.insertKey(h);
    cout<<"\n"<<binaryTree.insertKey(i);
    cout<<"\n"<<binaryTree.insertKey(j);

    cout<<endl;
    binaryTree.display();

    BstNode<int>* searchResult = binaryTree.forSearch(f);
    cout<<"search element: "<<searchResult->data.key<<endl;

    return 0;
}
