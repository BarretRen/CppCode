#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP
#include <iostream>
#include <queue>

template<typename T>
class TreeNode
{
public:
    TreeNode()
    {
        leftChild = nullptr;
        rightChild = nullptr;
    }
    T data;
    TreeNode<T>* leftChild;
    TreeNode<T>* rightChild;
};

template<typename T>
class BinaryTree
{
public:
    //二叉树的遍历操作
    void InOrder(TreeNode<T>* currentNode);//中序遍历：左子树-节点-右子树
    void PreOrder(TreeNode<T>* currentNode);//前序遍历 节点-左子树-右子树
    void PostOrder(TreeNode<T>* currentNode);//后续遍历 左子树-右子树-节点
    void LevelOrder(TreeNode<T>* currentNode);//层序遍历, 一层一层显示value
    
    void showNodeValue(TreeNode<T>* currentNode);
    
    TreeNode<T>* root;   
};

template <typename T>
void BinaryTree<T>::InOrder(TreeNode<T>* currentNode)
{
    if (currentNode)
    {
        //左子树递归
        InOrder(currentNode->leftChild);
        //显示当前节点
        showNodeValue(currentNode);
        //右子树递归
        InOrder(currentNode->rightChild);
    }
}

template <typename T>
void BinaryTree<T>::PreOrder(TreeNode<T>* currentNode)
{
    if (currentNode)
    {
        //显示当前节点
        showNodeValue(currentNode);
        //左子树递归
        PreOrder(currentNode->leftChild);
        //右子树递归
        PreOrder(currentNode->rightChild);
    }
}

template <typename T>
void BinaryTree<T>::PostOrder(TreeNode<T>* currentNode)
{
    if (currentNode)
    {
        //左子树递归
        PostOrder(currentNode->leftChild);
        //右子树递归
        PostOrder(currentNode->rightChild);
        //显示当前节点
        showNodeValue(currentNode);
    }
}

template <typename T>
void BinaryTree<T>::LevelOrder(TreeNode<T>* currentNode)
{
    std::queue<TreeNode<T>*> q;//保存未显示的节点
    while (currentNode)
    {
        showNodeValue(currentNode);
        //显示当前节点后，将其左右子树加入队列
        if (currentNode->leftChild)
            q.push(currentNode->leftChild);
        if (currentNode->rightChild)
            q.push(currentNode->rightChild);

        if (q.empty())
            return;

        currentNode = q.front();//设置下次循环从队列去除一个新的节点
        q.pop();//删除队列第一个

    }

}

template <typename T>
void BinaryTree<T>::showNodeValue(TreeNode<T>* currentNode)
{
    std::cout<<currentNode->data;
}
#endif
