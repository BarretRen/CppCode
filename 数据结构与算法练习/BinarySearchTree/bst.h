#ifndef BST_H
#define BST_H
#include <iostream>

template<typename T> class BST;//前置声明

template<typename T>
class Element
{
public:
    T key;//将键值单独一个类放置，方便扩展数据结构
};

template<typename T>
class BstNode
{
    friend class BST<T>;//友元类，可以访问私有成员
public:
    Element<T> data;
private:
    BstNode* leftChild;
    BstNode* rightChild;
};

template<typename T>
class BST
{
public:
    BST(BstNode<T>* init = 0)
    {
        root = init;
    }
    bool insertKey(const Element<T>& ele); //插入数据
    BstNode<T>* search(const Element<T>& ele);
    BstNode<T>* search(BstNode<T>* start, const Element<T>& ele);//递归查找数据
    BstNode<T>* forSearch(const Element<T>& ele);//迭代查找数据
    void display()
    {
        if (root)
            display(root);
        else
            std::cout<<"no nodes"<<std::endl;
    }
    void display(BstNode<T>* node);//显示节点数据
private:
    BstNode<T>* root;
};

template<typename T>
void BST<T>::display(BstNode<T>* node)
{
    if (!node)
    {
        return;
    }
    //显示当前节点及其左右子树的key
    std::cout<<"data.key: "<<node->data.key<<std::endl;
    if (node->leftChild)
    {
        display(node->leftChild);
    }
    if (node->rightChild)
    {
        display(node->rightChild);
    }
}

template<typename T>
bool BST<T>::insertKey(const Element<T>& ele)
{
    BstNode<T>* p = root;
    BstNode<T>* q = nullptr; //q为p的父节点
    //插入之前需要先查找，找到合适的位置
    while (p)
    {
        q = p; //p改变之前，q指向当前节点
        if (ele.key == p->data.key)
        {
            return false;//值重复，失败返回
        }
        else if (ele.key < p->data.key)
        {
            //小于，继续查找当前节点左子树
            p = p->leftChild;
        }
        else
        {
            //大于，继续查找当前节点右子树
            p = p->rightChild;
        }
    }
    //循环结束，合适的位置就是q
    p = new BstNode<T>;//创建新节点
    p->leftChild = nullptr;
    p->rightChild = nullptr;
    p->data = ele;
    if (!root)
        root = p; //没有根节点，p就是根节点
    else if (ele.key < q->data.key)
    {
        q->leftChild = p;
    }
    else
    {
        q->rightChild = p;
    }

    return true;
}

template<typename T>
BstNode<T>* BST<T>::search(const Element<T>& ele)
{
    if (root)
        return search(root, ele);
    else
        return nullptr;
}

template<typename T>
BstNode<T>* BST<T>::search(BstNode<T>* start, const Element<T>& ele)
{
    if (!start)
        return nullptr;

    if (start->data.key == ele.key)
    {
        return start;
    }
    else if (start->data.key > ele.key)
    {
        return search(start->leftChild, ele);
    }
    else
    {
        return search(start->rightChild, ele);
    }
}

template<typename T>
BstNode<T>* BST<T>::forSearch(const Element<T>& ele)
{
    for (BstNode<T>* n = root; n != nullptr; )
    {
        if (ele.key == n->data.key)
        {
            return n;
        }
        else if (ele.key < n->data.key)
        {
            n = n->leftChild;
        }
        else
        {
            n = n->rightChild;
        }
    }
     return nullptr;
}
#endif // BST_H
