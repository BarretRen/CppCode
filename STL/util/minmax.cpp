//辅助函数：获取最大值最小值
#include <algorithm>
#include <iostream>
using namespace std;

int main()
{
    int x = 17;
    int y = 42;
    int z = 33;

    //调用min第一版本
    cout << min(17, 42) << endl;
    cout << min(x, y) << endl;

    //调用min第二版本
    cout << min({x, y, z}) << endl;
}