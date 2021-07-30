//�����ڴ�й©�Ĵ���ʾ������MSVC���Լ���ڴ����
#include <iostream>

//����msvc����ͷ�ļ�
#define _CRTDGB_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

//�ض���new�����
#ifdef _DEBUG
#ifndef _DGB_NEW
#define DGB_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DGB_NEW
#endif // _DGB_NEW
#endif // _DEBUG

class Simple
{
public:
    //���������û�����⣬new/delete�ɶԳ���
    Simple() : mIntPtr(new int[1024]) {}
    ~Simple() { delete mIntPtr; }

    void DoSomeThing(Simple *&outParam)
    {
        outParam = new Simple();
        //���������⣬outParamֱ��ָ���´����Ķ���ԭ������Ķ���û���ͷ�
    }

protected:
    int *mIntPtr;
};

int main(int argc, char **argv)
{
    //�����ڴ���
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    auto simplePtr = new Simple;
    simplePtr->DoSomeThing(simplePtr);

    std::cout << "Hello world" << std::endl;

    return 0;
}