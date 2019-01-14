#include <iostream >
#include <string >

int main () {
	std :: string str = R"(C:\\What\\The\\Path )";
	std :: cout << str << std :: endl ;

	std :: string str2 = "(C:\\What\\The\\Path )";
	std :: cout << str2 << std :: endl ;
	return 0;
}