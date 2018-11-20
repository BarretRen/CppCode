#ifndef ITERATOR_HPP_INCLUDED
#define ITERATOR_HPP_INCLUDED

class Collection;

class Iterator
{
public:
    Iterator(){};
    Iterator(Collection* c, int idx=0);
    void first();
    void next();
    bool isDone();
    int currentItem();
private:
    Collection* _c;
    int _idx;
};

#endif // ITERATOR_HPP_INCLUDED
