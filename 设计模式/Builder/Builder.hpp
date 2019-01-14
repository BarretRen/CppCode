#ifndef BUILDER_HPP_INCLUDED
#define BUILDER_HPP_INCLUDED
#include "Product.hpp"
#include <string>
using namespace std;



class Builder
{
public:
    virtual ~Builder();
    virtual void buildPartA(const string& buildPartA)=0;
    virtual void buildPartB(const string& buildPartB)=0;
    virtual void buildPartC(const string& buildPartC)=0;
    virtual Product* getProduct()=0;
protected:
    Builder();
};

class SubBuilder:public Builder
{
public:
    SubBuilder();
    ~SubBuilder();
    void buildPartA(const string& buildPartA);
    void buildPartB(const string& buildPartB);
    void buildPartC(const string& buildPartC);
    Product* getProduct();
};
#endif // BUILDER_HPP_INCLUDED
