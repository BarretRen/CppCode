//���Ƴ�ʼ���б��ֱ�ӳ�ʼ���б������
//C++17֮����ܵ��±������
#include <initializer_list>

int main()
{
    // Copy list initialization
    auto a = {11};     // auto = initializer_list<int>
    auto b = {11, 22}; // auto = initializer_list<int>

    // Direct list initialization
    auto c{11};     // auto = int
    auto d{11, 22}; // auto = int�����ж��ֵ. Error, too many elements.
}