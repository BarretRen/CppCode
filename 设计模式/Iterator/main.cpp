#include <iostream>
#include "Collection.hpp"
#include "Iterator.hpp"
using namespace std;

int main()
{
    Collection* c=new Collection();
    Iterator* I=c->createIterator();

    for(;!(I->isDone());I->next())
    {
        cout<<I->currentItem()<<endl;
    }
    return 0;
}
