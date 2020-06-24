/*
排列组合，列出几个字符之间所有的组合
*/
#include <iostream>

using namespace std;

//使用递归，排列组合函数
//start为p中起始位置，end为结束位置
void permutations(char* p, const int start, const int end)
{
    if (start == end)
    {
        //起始字符到结束字符，组合结束，输出p
        cout<<p<<endl;
    }
    else
    {
        for (int i = start; i <= end; i++)
        {
            swap(p[start], p[i]);//交换起始字符和下一字符
            permutations(p, start + 1, end); //再组合一下去除首字符之后所有字符的组合
            swap(p[start], p[i]); //还原位置
        }
    }
}

int main()
{
    char p[] = "abc";
    permutations(p, 0, 2);
    
    return 0;
}