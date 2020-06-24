#ifndef INTERPRETER_HPP_INCLUDED
#define INTERPRETER_HPP_INCLUDED
class Context
{
public:
    Context() {};
    ~Context() {};
};

#include <string>
using namespace std;
class AbstractExpression
{
public:
    virtual ~AbstractExpression();
    virtual void Interpret(const Context& c);
protected:
    AbstractExpression();
private:
};
class TerminalExpression:public AbstractExpression
{
public:
    TerminalExpression(const string& statement);
    ~ TerminalExpression();
    void Interpret(const Context& c);
protected:
private:
    string _statement;
};
class NonterminalExpression:public AbstractExpression
{
public:
    NonterminalExpression(AbstractExpression* expression,int times);
    ~ NonterminalExpression();
    void Interpret(const Context& c);
protected:
private:
    AbstractExpression* _expression;
    int _times;
};


#endif // INTERPRETER_HPP_INCLUDED
