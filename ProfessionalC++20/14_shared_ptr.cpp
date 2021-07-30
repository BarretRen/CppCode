#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

int main()
{
    //����shared pointer�����ַ�ʽ
    //shared_ptr<string> p1(new string("nico"));
    shared_ptr<string> p1(new string("nico"), [](string* p) { //���ַ�ʽ�������Զ���deleter
        cout << "delete " << *p << " in customer deleter" << endl;
        delete p;
        });
    shared_ptr<string> p2 = make_shared<string>("jutta");//�Ƽ�ʹ��

    //C++20���룬�Զ�����Ĭ��ֵ��ʼ��
    shared_ptr<string> p3 = make_shared_for_overwrite<string>();//Ĭ�Ͽ��ַ���

    //���vector
    vector<shared_ptr<string>> whoMadeCoffee;
    whoMadeCoffee.push_back(p2);
    whoMadeCoffee.push_back(p2);
    whoMadeCoffee.push_back(p1);
    whoMadeCoffee.push_back(p2);
    whoMadeCoffee.push_back(p1);
    whoMadeCoffee.push_back(p3);

    //��ӡvector
    for (auto vec : whoMadeCoffee)
    {
        cout << *vec << "  "; //vec�ǹ���ָ��
    }
    cout << endl;

    //����ָ���޸�����
    (*p1)[0] = 'N';
    p2->replace(0, 1, "J");

    //���´�ӡvector�����ݱ��޸�
    for (auto vec : whoMadeCoffee)
    {
        cout << *vec << "  ";
    }
    cout << endl;

    //��ӡָ������ü���
    cout << "p1 count:" << p1.use_count() << endl; //��ӡ3
    cout << "p2 count:" << p2.use_count() << endl; //��ӡ4
    cout << "p2 count:" << p3.use_count() << endl; //��ӡ2
    return 0;
}