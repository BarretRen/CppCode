#include <iostream>
#include "maxheap.h"

using namespace std;

int main()
{
    MaxHeap<int> h(100);
    cout<<h.isEmpty()<<endl;

    h.push(20);
    h.push(30);
    h.push(15);
    h.push(90);
    h.push(35);

    cout<<h.Top()<<endl;
    h.pop();
    cout<<h.Top()<<endl;

    cout << "Hello World!" << endl;
    return 0;
}
