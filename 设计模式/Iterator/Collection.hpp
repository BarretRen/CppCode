#ifndef COLLECTION_HPP_INCLUDED
#define COLLECTION_HPP_INCLUDED

const int SIZE=3;
class Iterator;

class Collection
{
public:
    Collection();
    ~Collection(){};
    Iterator* createIterator();

private:
    friend class Iterator;
    int lst[SIZE];
    int getItem(int index);
};

#endif // COLLECTION_HPP_INCLUDED
