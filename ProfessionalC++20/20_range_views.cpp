//使用range adapter创建view，不同的adapter代表不同的操作
#include <algorithm>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>
using namespace std;

void printRange(string_view message, auto& range)
{
	cout << message;
	for (const auto& value : range) {
		cout << value << " ";
	}
	cout << endl;
}

int main()
{
	vector values{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	printRange("原始容器数据: ", values);

	//创建filter view，并设置筛选函数
	auto result1{ values | views::filter([](const auto& value) { return value % 2 == 0; }) };
	printRange("filter view values: ", result1);

	//创建transform view，修改view数据
	/*auto result2{ result1 | views::transform([](const auto& value) { return value * 2.0; }) };
	printRange("transform view，Values doubled: ", result2);*/

	// drop view，跳过前两个数据
	auto result3{ result1 | views::drop(2) };
	printRange("Drop view，First two dropped: ", result3);

	// Reverse view. 反向迭代
	auto result4{ result3 | views::reverse };
	printRange("Reverse view: ", result4);

	//view之后看看原始数据
	printRange("view后容器数据: ", values);

	// Modify the elements using a range-based for loop.
	for (auto& value : result4) { value *= 10; }
	printRange("After modifying elements through a view, vector contains: ", values);
}