#include "Builder.hpp"
#include <iostream>
using namespace std;

Builder::Builder()
{

}
Builder::~Builder()
{

}
SubBuilder::SubBuilder()
{

}
SubBuilder::~SubBuilder()
{

}

void SubBuilder::buildPartA(const string& buildPartA)
{
    cout<<"Step1: build Product Part A..."<<buildPartA<<endl;
}

void SubBuilder::buildPartB(const string& buildPartB)
{
    cout<<"Step1: build Product Part B..."<<buildPartB<<endl;
}

void SubBuilder::buildPartC(const string& buildPartC)
{
    cout<<"Step1: build Product Part C..."<<buildPartC<<endl;
}

Product* SubBuilder::getProduct()
{
    cout<<"get your product"<<endl;
    return new Product();
}
