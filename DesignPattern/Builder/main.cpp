#include <iostream>
#include "Director.hpp"
#include "Product.hpp"
#include "Builder.hpp"
using namespace std;

int main()
{
    Director* d=new Director(new SubBuilder());
    //���ò�Ʒ�ĸ�������
    d->Construct(/*������Ը�Ϊ�����������*/);
    //�õ���Ʒ
    d->getMyProduct();
    return 0;
}
