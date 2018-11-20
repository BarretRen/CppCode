//产品工厂的cpp文件,Factory.cpp
#include "Factory.h"
#include "Product.h"
#include <iostream>
using namespace std;

Factory::Factory()
{
	//TODO
}

Factory::~Factory()
{
	//TODO
}

SubFactory::SubFactory()
{
	cout<<"SubFactory create function..."<<endl;
}

SubFactory::~SubFactory()
{

}

Product* SubFactory::createProduct()
{
	return new SubProduct();
}
