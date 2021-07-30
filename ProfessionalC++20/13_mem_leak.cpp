//存在内存泄漏的代码示例，用MSVC调试检测内存错误
#include <iostream>

//引入msvc调试头文件
#define _CRTDGB_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

//重定义new运算符
#ifdef _DEBUG
#ifndef _DGB_NEW
#define DGB_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DGB_NEW
#endif // _DGB_NEW
#endif // _DEBUG

class Simple
{
public:
    //构造和析构没有问题，new/delete成对出现
    Simple() : mIntPtr(new int[1024]) {}
    ~Simple() { delete mIntPtr; }

    void DoSomeThing(Simple *&outParam)
    {
        outParam = new Simple();
        //这里有问题，outParam直接指向新创建的对象，原来传入的对象没有释放
    }

protected:
    int *mIntPtr;
};

int main(int argc, char **argv)
{
    //开启内存检测
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    auto simplePtr = new Simple;
    simplePtr->DoSomeThing(simplePtr);

    std::cout << "Hello world" << std::endl;

    return 0;
}