#include <iostream>
#include "Director.hpp"
#include "Product.hpp"
#include "Builder.hpp"
using namespace std;

int main()
{
    Director* d=new Director(new SubBuilder());
    //设置产品的各个属性
    d->Construct(/*这里可以改为传入各个参数*/);
    //得到产品
    d->getMyProduct();
    return 0;
}
