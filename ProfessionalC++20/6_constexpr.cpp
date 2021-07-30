#include <iostream>

using namespace std;

class Rect
{
public:
	constexpr Rect(size_t width, size_t height) : m_width{ width }, m_height{ height } {}
	constexpr size_t getArea() const { return m_width * m_height; }
private:
	size_t m_width{ 0 }, m_height{ 0 };
};

constexpr int getArraySize(int a)
{
	return 32 + a;
}

consteval int getArraySize2(int b)
{
	return 32 - b;
}

int main()
{
	//��������
	constexpr Rect r{ 8, 2 };//����constexpr���캯��
	int myArray[r.getArea()];
	cout << std::size(myArray) << endl;

	constexpr int a{ 8 };
	int myArray2[getArraySize(a)]; // �����ڱ����ڿ��Ե��÷���32+a
	cout << std::size(myArray2) << endl;

	constexpr int b{ 8 };
	int myArray3[getArraySize2(b)];
	cout << std::size(myArray3) << endl;
}