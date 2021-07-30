//使用iterator_traits的示例，可以获取迭代器的信息
#include <iterator>
#include <iostream>
#include <format>
#include <vector>
using namespace std;

//因为此模板函数中，不知道迭代器指向的什么类型的数据
//所有创建一个iterator_traits，然后返回value_type作为函数参数类型
template <typename Iter>
auto myFind(Iter begin, Iter end,
	const typename iterator_traits<Iter>::value_type& value)
{
	for (auto iter{ begin }; iter != end; ++iter) {
		if (*iter == value) { return iter; }
	}
	return end;
}

int main()
{
	vector values{ 11, 22, 33, 44 };//根据赋值自动推导出vector中都是int类型数据
	auto result{ myFind(cbegin(values), cend(values), 22) };
	if (result != cend(values))
	{
		//打印迭代器间的举例
		cout << format("Found value at position {}", distance(cbegin(values), result));
	}
}