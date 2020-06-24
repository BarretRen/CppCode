#include <vector>  //容器
#include <algorithm> //算法
#include <functional> //仿函数
#include <iostream>

using namespace std;

int main()
{
    int a[6] = {27, 210, 12, 47, 109, 83};
    //容器vector同时指定保存的类型和分配器，一次将数据导入
    vector<int, allocator<int>> vec(a, a+6);
    
    /*begin(),end()是迭代器
    * count_if是某个算法，计算符合条件的个数
    * not1是否定的函数适配器，取否
    * bind2nd是绑定第二个参数的函数适配器，即第二个参数绑定是40
    * less是比大小的仿函数，小于
    * 综合一下即：计算vec中大于等于40的数的个数*/
    cout<<count_if(vec.begin(), vec.end(), not1(bind2nd(less<int>(), 40))); 
    
    return 0;
}