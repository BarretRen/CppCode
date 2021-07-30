#include <format>
#include <iostream>

// ���� T �İ�װ
template<class T>
struct Box {
	T value;
};

// ���ñ���װֵ�ĸ�ʽ˵����ʽ����װ Box<T>
template<class T, class CharT>
struct std::formatter<Box<T>, CharT> : std::formatter<T, CharT>
{
	// �ӻ���̳�parse()���������Ҫ�̳У�����Ҫ�̳и���

	// ͨ���Ա���װֵ���û���ʵ�ֶ��� format()
	template<class FormatContext>
	auto format(Box<T> t, FormatContext& fc) {
		return std::formatter<T, CharT>::format(t.value, fc);
	}
};

int main()
{
	Box<int> v = { 42 };
	std::cout << std::format("{:#x}", v);
}