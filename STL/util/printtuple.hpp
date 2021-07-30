//重载<<运算符，支持打印tuple
#include <tuple>
#include <iostream>

template <int IDX, int MAX, typename... Args>
class PRINT_TUPLE
{
public:
    static void print(std::ostream &strm, const std::tuple<Args...> &t)
    {
        strm << std::get<IDX>(t) << (IDX + 1 == MAX ? "" : ",");
        PRINT_TUPLE<IDX + 1, MAX, Args...>::print(strm, t);
    }
};

template <int MAX, typename... Args>
class PRINT_TUPLE<MAX, MAX, Args...>
{
public:
    static void print(std::ostream &strm, const std::tuple<Args...> &t)
    {
        //最后一个，什么都不需要打印
    }
};

template <typename... Args>
std::ostream &operator<<(std::ostream &strm, const std::tuple<Args...> &t)
{
    strm << "[";
    PRINT_TUPLE<0, sizeof...(Args), Args...>::print(strm, t);
    return strm << "]";
}