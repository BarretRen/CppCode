//程序入口，main.cpp
#include "Factory.h"
#include "Product.h"
#include <iostream>
using namespace std;

int main()
{
	//创建子工厂类
	Factory* factory = new SubFactory();
	//生产子产品
	Product* product = factory->createProduct();

	return 0;
}
