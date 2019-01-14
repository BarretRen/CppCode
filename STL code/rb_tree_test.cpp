#include <bits/stl_tree.h>
#include <iostream>

using namespace std;

int main()
{
    _Rb_tree<int, int, _Identity<int>, less<int>> tree;
    cout<<tree.empty()<<endl; //1
    cout<<tree.size()<<endl; //0
    
    tree._M_insert_unique(3);
    tree._M_insert_unique(8);
    tree._M_insert_unique(5);
    tree._M_insert_unique(9);
    tree._M_insert_unique(13);
    tree._M_insert_unique(5); //no effect
    
    cout<<tree.empty()<<endl; //0
    cout<<tree.size()<<endl; //5
    cout<<tree.count(5)<<endl;//返回值为5的个数
    
    tree._M_insert_equal(5);//可以插入相同值
    tree._M_insert_equal(5);
    cout<<tree.size()<<endl; //7
    cout<<tree.count(5)<<endl;//3
    return 0;
}