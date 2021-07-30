//ʹ��range projectionӳ�������
//�ڵ���������ǰ��ʹ��ӳ��ص��Ƚ�Person�����С
#include <ranges>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Person
{
public:
	Person(string first, string last)
		: m_firstName{ move(first) }, m_lastName{ move(last) } {}
	const string& getFirstName() const { return m_firstName; }
	const string& getLastName() const { return m_lastName; }

private:
	string m_firstName;
	string m_lastName;
};

int main()
{
	vector persons{ Person {"John", "White"}, Person {"Chris", "Blue"} };
	//���Խ�������
	//sort(begin(persons), end(persons)); // Error: does not compile
	//ranges::sort(persons); // Error: does not compile

	//ʹ��ӳ�䣬����sortʹ��ʲô�����ж�Person��С
	ranges::sort(persons, {}, &Person::getFirstName);
	for (auto person : persons)
	{
		cout << person.getFirstName() << " " << person.getLastName() << endl;
	}
	return 0;
}