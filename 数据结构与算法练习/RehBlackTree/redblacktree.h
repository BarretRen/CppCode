#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H
#include "except.h"

template <class T>
class RedBlackTree;

template <typename T>
class RedBlackNode;

//红黑树
template <typename T>
class RedBlackTree
{
public:
    enum {RED, BLACK};
    typedef RedBlackNode<T> Node;

    RedBlackTree(const T& negInf);
    ~RedBlackTree();

    void insert(const T& x);
    void rotateWithLeftChild(Node* & K2) const; //单旋转，向右
    void rotateWithRightChild(Node* & k1) const; //单旋转，向左
    void doubleRotateWithLeftChild(Node* & K2) const; //双旋转
    void doubleRotateWithRightChild(Node* & k1) const;//双旋转
    void handleReorient(const T& item); //平滑处理
    RedBlackNode<T>* rotate(const T& item, Node* parent); //旋转函数

    bool isEmpty();
    void makeEmpty();
    void deleteNodes(Node* start);//删除从start开始往后所有节点

    bool find(const T& x, Node* node);
    bool findMin(T& value);
    bool findMax(T& value);

    //private:  //just for test
    Node* header; //指向root根节点的指针
    Node* nullNode; //无子节点

    Node* current;
    Node* parent; //父节点
    Node* grand; //祖父节点
    Node* great; //曾祖父节点
};

//红黑树节点
template <typename T>
class RedBlackNode
{
public:
    friend class RedBlackTree<T>;
    RedBlackNode(const T& theElement = T(),
                 RedBlackNode* lt = nullptr,
                 RedBlackNode* rt = nullptr,
                 int c = RedBlackTree<T>::BLACK)
    {
        element = theElement;
        left = lt;
        right = rt;
        color = c;
    }
    //private:
    T element;
    RedBlackNode* left;
    RedBlackNode* right;
    int color; //颜色
};

template <typename T>
RedBlackTree<T>::RedBlackTree(const T& neginf)
{
    nullNode = new Node();
    nullNode->left = nullNode->right = nullNode;

    //构造函数指定header为负无穷大
    header = new Node(neginf);
    header->left = header->right = nullNode;
}

template <typename T>
RedBlackTree<T>::~RedBlackTree()
{
    makeEmpty();
    delete nullNode;
    delete header;
}

template <typename T>
void RedBlackTree<T>::insert(const T& x)
{
    current = parent = grand = header;
    nullNode->element = x;
    //查找位置
    while (current->element != x)
    {
        great = grand;
        grand = parent;
        parent = current;

        current = x < current->element ? current->left : current->right;

        //检查：如果当前节点，左右儿子节点都是红色，需要处理
        if (current->left->color == RED && current->right->color == RED)
        {
            handleReorient(x);
        }
    }

    if (current != nullNode)
        throw  DuplicateItemException();

    current = new Node(x, nullNode, nullNode);
    if (x < parent->element)
        parent->left = current;
    else
        parent->right = current;

    //自动平滑当前树，变为红黑树(重点)
    handleReorient(x);
}

//向右旋转
template <typename T>
void RedBlackTree<T>::rotateWithLeftChild(Node* & k2) const
{
    Node* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2 = k1;
}

//向左旋转
template <typename T>
void RedBlackTree<T>::rotateWithRightChild(Node* & k1) const
{
    Node* k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1 = k2;
}

template <typename T>
void RedBlackTree<T>::doubleRotateWithLeftChild(Node* & k2) const
{
    rotateWithRightChild(k2->left);
    rotateWithLeftChild(k2);
}

template <typename T>
void RedBlackTree<T>::doubleRotateWithRightChild(Node* & k1) const
{
    rotateWithLeftChild(k1->right);
    rotateWithRightChild(k1);
}

template <typename T>
void RedBlackTree<T>::handleReorient(const T& item)
{
    //变色
    current->color = RED;
    current->left->color = BLACK;
    current->right->color = BLACK;

    if (parent->color == RED)
    {
        grand->color = RED;
        if ((item < grand->element) != (item < parent->element))
        {
            parent = rotate(item, grand);//单旋转
        }
        current = rotate(item, great);//双旋转
        current->color = BLACK;
    }
    header->right->color = BLACK;
}

/*
 * 左子树向右转--LL
 * 左子树向左转--LR
 * 右子树向右转--RL
 * 右子树向左转--RR
 */
template <typename T>
RedBlackNode<T>* RedBlackTree<T>::rotate(const T& item, Node* parent)
{
    if (item < parent->element)
    {
        item < parent->left->element ? rotateWithLeftChild(parent->left)
                                     : rotateWithRightChild(parent->left);
        return parent->left;
    }
    else
    {
        item < parent->right->element ? rotateWithLeftChild(parent->right)
                                      : rotateWithRightChild(parent->right);
        return parent->right;
    }
}

template <typename T>
bool RedBlackTree<T>::isEmpty()
{
    return header->right == nullNode;
}

template <typename T>
void RedBlackTree<T>::makeEmpty()
{
    deleteNodes(header->right);
    header->right = nullNode;
}

template <typename T>
void RedBlackTree<T>::deleteNodes(Node* start)
{
    //使用递归
    if (start != start->left)
    {
        deleteNodes(start->left);
        deleteNodes(start->right);
        delete start;
    }
}

template <typename T>
bool RedBlackTree<T>::find(const T& x, Node* node)
{
    if(isEmpty())
        return false;

    nullNode->element = x;
    Node* start = header->right;
    for(;;)
    {
        if (x < start->element)
        {
            start = start->left;
        }
        else if (x > start->element)
        {
            start = start->right;
        }
        else if (start != nullNode)
        {
            node->element = start->element;
            return true;
        }
        else
            return false;
    }
}

template <typename T>
bool RedBlackTree<T>::findMin(T& value)
{
    if(isEmpty())
        return false;

    //一直向左查找最小
    Node* node = header->right;
    while (node->left != nullNode)
    {
        node = node->left;
    }

    value = node->element;
    return true;
}

template <typename T>
bool RedBlackTree<T>::findMax(T& value)
{
    if(isEmpty())
        return false;

    //一直向左查找最小
    Node* node = header->right;
    while (node->right != nullNode)
    {
        node = node->right;
    }

    value = node->element;
    return true;
}
#endif // REDBLACKTREE_H
