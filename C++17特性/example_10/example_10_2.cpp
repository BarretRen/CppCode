#include <iostream>
#include <utility>

void reference ( int & v) {
	std :: cout << " 左 值 " << std :: endl ;
}
void reference ( int && v) {
	std :: cout << " 右 值 " << std :: endl ;
}
template <typename T>
void pass (T&& v) {
	std :: cout << " 普 通 传 参 :";
	reference (std::forward<T>(v)); // 始 终 调 用 reference ( int & )
}

int main () {
	std :: cout << " 传 递 右 值 :" << std :: endl;
	pass (1); // 1 是 右 值 , 但 输 出 左 值，有了forward之后为右值

	std :: cout << " 传 递 左 值 :" << std :: endl;
	int v = 1;
	pass (v); // r 是 左 引 用 , 输 出 左 值

	return 0;
}