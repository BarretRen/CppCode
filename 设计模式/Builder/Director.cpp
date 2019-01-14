#include "Director.hpp"
#include "Builder.hpp"

Director::Director(Builder* bld)
{
    _bld=bld;
}
Director::~Director()
{

}
void Director::Construct()
{
    _bld->buildPartA("user-defined 1");
    _bld->buildPartB("user-defined 2");
    _bld->buildPartC("user-defined 3");
}

Product* Director::getMyProduct()
{
    return _bld->getProduct();
}
