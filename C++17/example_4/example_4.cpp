#include <iostream>
#include <vector>
#include <initializer_list> //需要添加这个头文件

class Foo
{
public:
    std::vector<int> vec;

    Foo(std::initializer_list<int> list) //初始化列表构造函数
    {
        for (std::initializer_list<int>::iterator it=list.begin(); it!=list.end(); ++it)
            vec.push_back(*it);
    }
};

int main()
{
    //after C++11
    Foo foo = {1, 2, 3, 4, 5}; //类似数组的方式
    std::cout<<"foo values"<<std::endl;

    for (std::vector<int>::iterator it=foo.vec.begin(); it!=foo.vec.end(); ++it)
        std::cout<<*it<<std::endl;

    return 0;
}
