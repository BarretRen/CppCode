#include "Collection.hpp"
#include "Iterator.hpp"

Collection::Collection()
{
    for(int i=0;i<SIZE; i++)
        lst[i]=i;
}

Iterator* Collection::createIterator()
{
    return new Iterator(this);
}

int Collection::getItem(int index)
{
    if(index < SIZE)
        return lst[index];
    else
        return -1;
}
