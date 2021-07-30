//使用自定义的打印模板类，打印元组
#include "printtuple.hpp"
#include <tuple>
#include <iostream>
#include <string>
using namespace std;

int main()
{
    auto t = make_tuple(77, 1.1, "more light");
    cout << " print tuple:" << t << endl;
}