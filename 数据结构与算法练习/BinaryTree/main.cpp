#include <iostream>
#include "BinaryTree.hpp"

int main()
{
    BinaryTree<char> tree;
    TreeNode<char> jia,jian,cheng,chu,a,b,c,d,e;
    
    jia.data='+';
    jian.data='-';
    cheng.data='*';
    chu.data='/';
    a.data='A';
    b.data='B';
    c.data='C';
    d.data='D';
    e.data='E';
    
    tree.root=&jia;
    jia.leftChild = &jian;
    jia.rightChild = &e;
    jian.leftChild = &cheng;
    jian.rightChild = &d;
    cheng.leftChild = &chu;
    cheng.rightChild =&c;
    chu.leftChild = &a;
    chu.rightChild = &b;
    
    std::cout<<"中序遍历"<<std::endl;
    tree.InOrder(tree.root);
    std::cout<<std::endl;

    std::cout<<"前序遍历"<<std::endl;
    tree.PreOrder(tree.root);
    std::cout<<std::endl;

    std::cout<<"后序遍历"<<std::endl;
    tree.PostOrder(tree.root);
    std::cout<<std::endl;

    std::cout<<"层序遍历"<<std::endl;
    tree.LevelOrder(tree.root);
}
