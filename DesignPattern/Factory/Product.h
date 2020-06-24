#ifndef PRODUCT_HPP_INCLUDED
#define PRODUCT_HPP_INCLUDED

class Product
{
public:
	virtual ~Product()=0;
protected:
	Product();
};

//子类定义
class SubProduct: public Product
{
public:
	SubProduct();
	~SubProduct();
};

#endif // PRODUCT_HPP_INCLUDED
