/*
使用标准库并行算法for_each的示例
*/
#include <algorithm>
#include <vector>
#include <iostream>
#include <execution>

void do_each(int &a)
{
    a++;
    std::cout << " after add, a = " << a << std::endl;
}

int main()
{
    std::vector<int> v = {1, 2, 3, 4, 5};
    // 使用并行算法，对vector中每个元素进行并行操作
    std::for_each(std::execution::par, v.begin(), v.end(), do_each);

    // 打印最后结果
    for (int i = 0; i < v.size(); i++)
    {
        std::cout << v[i] << "  " << std::endl;
    }
    return 0;
}
