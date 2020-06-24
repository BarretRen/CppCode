#include <iostream>
#include <initializer_list>

// template<typename T0, typename... T>
// void print(T0 t0, T... t)
// {
    // std::cout << t0 <<std::endl;
    // if constexpr (sizeof...(t) > 0) printf(t...);
// }

template<typename T0, typename... T>
auto print(T0 t0, T... t)
{
    std::cout << t0 << std::endl;
    return std::initializer_list<T0>{ //中括号里是lambda表达式
        ([&] {
            std::cout << t << std::endl;
         }(), t0)...};
}

int main()
{
    print(1, 2, "123", 1.1);
    return 0;
}
