#ifndef HANDLE_HPP_INCLUDED
#define HANDLE_HPP_INCLUDED

class Handle
{
public:
    virtual ~Handle()
    {
        delete _succ;
    };
    virtual void handleRequest()=0;
    void setSuccessor(Handle* succ)
    {
        _succ=succ;
    };
    Handle* getSuccessor()
    {
        return _succ;
    };
protected:
    Handle()
    {
        _succ=0;
    };
    Handle(Handle* succ)
    {
        _succ=succ;
    };
private:
    Handle* _succ;
};

class ConcreteHandleA:public Handle
{
public:
    ConcreteHandleA(){};
    ~ConcreteHandleA(){};
    ConcreteHandleA(Handle* succ):Handle(succ){};
    void handleRequest();
};

class ConcreteHandleB:public Handle
{
public:
    ConcreteHandleB(){};
    ~ConcreteHandleB(){};
    ConcreteHandleB(Handle* succ):Handle(succ){};
    void handleRequest();
};

#endif // HANDLE_HPP_INCLUDED
