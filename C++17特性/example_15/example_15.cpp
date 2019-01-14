#include <iostream>
#include <array>

int main(){
	int myArray[]={1,2,3,4};
	std::cout<<sizeof(myArray)<<std::endl;
	std::cout<<std::size(myArray)<<std::endl;
	return 0;
}