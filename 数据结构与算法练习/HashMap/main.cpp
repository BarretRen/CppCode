#include <iostream>
#include "hashmap.h"
#include <string>

using namespace std;

int main()
{
    HashMap<string, int> map;
    map.Put("Bill", 999);
    map.Put("Tom", 888);
    map.Put("Mary", 777);

    cout << map.Get("Bill") << endl;
    return 0;
}
