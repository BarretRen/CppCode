#include <iostream>

class Base {
    public :
        int value1 ;
        int value2 ;
        Base () {
            value1 = 1;
        }
        Base ( int value ) : Base () { // 委 托 Base () 构 造 函 数
            value2 = value;
        }
};

class Subclass : public Base {
    public :
        using Base :: Base ; // 继 承 构 造
};

int main () {
    Base b(2);
    std :: cout << b. value1 << std :: endl ;
    std :: cout << b. value2 << std :: endl ;


    Subclass s(3);
    std :: cout << s. value1 << std :: endl ;
    std :: cout << s. value2 << std :: endl ;
}
