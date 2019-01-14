#include "Collection.hpp"
#include "Iterator.hpp"

Iterator::Iterator(Collection* c, int idx)
{
    _c=c;
    _idx=idx;
}

void Iterator::first()
{
    _idx=0;
}

void Iterator::next()
{
    if(_idx < SIZE)
        _idx++;
}

bool Iterator::isDone()
{
    return (_idx == SIZE);
}

int Iterator::currentItem()
{
    return _c->getItem(_idx);
}
