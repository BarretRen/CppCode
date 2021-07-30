//使用range projection映射的例子
//在调用排序函数前，使用映射回调比较Person对象大小
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
	//尝试进行排序
	//sort(begin(persons), end(persons)); // Error: does not compile
	//ranges::sort(persons); // Error: does not compile

	//使用映射，告诉sort使用什么规则判断Person大小
	ranges::sort(persons, {}, &Person::getFirstName);
	for (auto person : persons)
	{
		cout << person.getFirstName() << " " << person.getLastName() << endl;
	}
	return 0;
}