#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    vector<int> vec;
    for (int i = 1; i < 10; i++)
        vec.push_back(i);
    
    ostream_iterator<int> iter(cout, ",");//创建迭代器的适配器
    std::copy(vec.begin(), vec.end(), iter);//复制vector中所有数据到适配器
    return 0;
}