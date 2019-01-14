#ifndef SINGLETON_HPP_INCLUDED
#define SINGLETON_HPP_INCLUDED

class Singleton
{
public:
    static Singleton* getInstance();
private:
    Singleton();
    static Singleton* instance;
};

#endif // SINGLETON_HPP_INCLUDED
