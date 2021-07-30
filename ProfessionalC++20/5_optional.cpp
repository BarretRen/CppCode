//std::optionalʹ��ʾ������ʾ���Դ��ڻ򲻴��ڵ�ֵ
#include <iostream>
#include <optional>

using namespace std;

//����һ������������ֵ�ǿ�ѡֵ���ȿ�����int��Ҳ����������������
optional<int> getData(bool it)
{
    if (it)
        return 42;
    return nullopt;
}

int main()
{
    //���ú��������淵��ֵ
    optional<int> data1{getData(true)};
    optional<int> data2{getData(false)};
    //�жϱ����Ƿ���ֵ(���ַ�ʽ)������д�ӡֵ
    if (data1.has_value())
    {
        cout << data1.value() << endl;
    }
    if (data2)
    {//�����ж�ֱ�ӷ��ʻ��׳�exception
        cout << *data2 << endl;
    }
    //data2û��ֵ��������ͨ�����·�ʽ��ӡ��������ʲô
    cout << "what is in data? " << data2.value_or(0) << endl;
}