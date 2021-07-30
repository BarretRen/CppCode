//函数指针的原始用法
#include <iostream>
#include <span>
#include <vector>
using namespace std;

//定义函数指针
using Matcher = bool (*)(int, int);
using MatchHandler = void (*)(size_t, int, int);
// typedef bool (*Matcher)(int, int);
// typedef void (*MatchHandler)(size_t, int, int);

//实际的函数实现
bool intEqual(int item1, int item2) { return item1 == item2; }

void printMatch(size_t position, int value1, int value2)
{
    printf("Match found at position %d (%d, %d)\r\n", position, value1, value2);
}
//使用函数指针作为参数
void findMatches(span<const int> values1, span<const int> values2,
                 Matcher matcher, MatchHandler handler)
{
    if (values1.size() != values2.size())
    {
        return;
    }
    for (size_t i{0}; i < values1.size(); ++i)
    {
        if (matcher(values1[i], values2[i]))
        {
            handler(i, values1[i], values2[i]);
        }
    }
}

int main()
{
    vector values1{2, 5, 6, 9, 10, 1, 1};
    vector values2{4, 4, 2, 9, 0, 3, 1};

    cout << "Calling findMatches() using intEqual():" << endl;
    //参数取函数地址
    findMatches(values1, values2, &intEqual, &printMatch);
}