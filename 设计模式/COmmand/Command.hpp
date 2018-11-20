#ifndef COMMAND_HPP_INCLUDED
#define COMMAND_HPP_INCLUDED

class Receiver;
typedef void (Receiver::* Action)();//定义函数指针

class Command
{
public:
    Command(Receiver* r)
    {
        _r=r;
    };
    Command(Receiver* r, Action act)
    {
        _r=r;
        _act=act;
    }
    ~Command()
    {
        if(_r)
            delete _r;
    };
    void execute()
    {
        _r->action();//第一种通知方式，调用接受者函数处理该消息
    };

    void execute2()
    {
        //第二种方式，调用callback方法处理
        (_r->*_act)();
    };
private:
    Receiver* _r;
    Action _act;
};

#endif // COMMAND_HPP_INCLUDED
