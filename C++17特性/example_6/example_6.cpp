#include <iostream>
#include <vector>

int main()
{
    std::vector<int> vec = {1,2,3,4,5};
    for (auto element : vec)
        std::cout << element << std::endl;

    for (auto &element : vec)   // wtire element
        element += 1;

    for (auto element : vec)     // read element
        std::cout << element << std::endl;

    int array[5] = {1,2,3,4,5};
    for (auto e : array)
        std::cout<<e<<std:tendl;
}
