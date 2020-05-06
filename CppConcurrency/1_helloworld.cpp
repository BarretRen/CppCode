// CppConcurrency.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <thread>

using namespace std;

void hello()//子线程将要执行的函数入口
{
    cout << "hello concurrent world" << endl;
}

int main1()
{
    thread th(hello);//创建一个子线程
    th.join();
    return 0;
}
