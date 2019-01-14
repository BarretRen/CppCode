#ifndef CONTEXT_HPP_INCLUDED
#define CONTEXT_HPP_INCLUDED
#include "Strategy.hpp"

/**
*�������Strategyģʽ�Ĺؼ���Ҳ��Strategyģʽ��Templateģʽ�ĸ����������ڡ�
*Strategyͨ������ϡ���ί�У���ʽʵ���㷨��ʵ�֣����칹����Templateģʽ���ȡ���Ǽ̳еķ�ʽ
*������ģʽ������Ҳ�Ǽ̳к��������ʵ�ֽӿ����õķ�ʽ������
*/

class Context
{
public:
    Context(Strategy* stg);
    ~Context();
    void doAction();
private:
    Strategy* _stg;
};

#endif // CONTEXT_HPP_INCLUDED
