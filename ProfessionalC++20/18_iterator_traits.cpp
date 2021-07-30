//ʹ��iterator_traits��ʾ�������Ի�ȡ����������Ϣ
#include <iterator>
#include <iostream>
#include <format>
#include <vector>
using namespace std;

//��Ϊ��ģ�庯���У���֪��������ָ���ʲô���͵�����
//���д���һ��iterator_traits��Ȼ�󷵻�value_type��Ϊ������������
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
	vector values{ 11, 22, 33, 44 };//���ݸ�ֵ�Զ��Ƶ���vector�ж���int��������
	auto result{ myFind(cbegin(values), cend(values), 22) };
	if (result != cend(values))
	{
		//��ӡ��������ľ���
		cout << format("Found value at position {}", distance(cbegin(values), result));
	}
}