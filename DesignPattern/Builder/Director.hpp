#ifndef DIRECTOR_HPP_INCLUDED
#define DIRECTOR_HPP_INCLUDED
#include "Product.hpp"
class Builder;

class Director
{
public:
    Director(Builder* bld);
    ~Director();
    void Construct();
    Product* getMyProduct();
private:
    Builder* _bld;
};

#endif // DIRECTOR_HPP_INCLUDED
