#include <iostream>
#include "redblacktree.h"

using namespace std;

int main()
{
    const int NEG_INF = -99999;
    //创建红黑树时，指定那个指向root的指针（即假的root)为无穷大，这样后面所有节点都在右边
    RedBlackTree<int> t(NEG_INF);

    t.insert(200);
    t.insert(100);
    t.insert(90);
    t.insert(50);
    t.insert(80);
    t.insert(70);
    t.insert(60);

    int a=0;
    if (t.findMin(a))
        cout<<a<<endl;
    if (t.findMax(a))
        cout<<a<<endl;

    RedBlackNode<int> tmp;
    if(t.find(65, &tmp))
    {
        cout<<"find"<<endl;
        cout<<tmp.element<<endl;
    }
    else
        cout<<"not found"<<endl;

    return 0;
}
