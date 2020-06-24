#ifndef COMMAND_HPP_INCLUDED
#define COMMAND_HPP_INCLUDED

class Receiver;
typedef void (Receiver::* Action)();//���庯��ָ��

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
        _r->action();//��һ��֪ͨ��ʽ�����ý����ߺ����������Ϣ
    };

    void execute2()
    {
        //�ڶ��ַ�ʽ������callback��������
        (_r->*_act)();
    };
private:
    Receiver* _r;
    Action _act;
};

#endif // COMMAND_HPP_INCLUDED
