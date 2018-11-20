#ifndef PROTOTYPE_HPP_INCLUDED
#define PROTOTYPE_HPP_INCLUDED

class Prototype
{
public:
    virtual ~Prototype();
    virtual Prototype* clone() const=0;
protected:
    Prototype();
};

class SubPrototype:public Prototype
{
public:
    SubPrototype();
    //¿½±´¹¹Ôìº¯Êý
    SubPrototype(const SubPrototype& sp);
    ~SubPrototype();
    Prototype* clone() const;
};
#endif // PROTOTYPE_HPP_INCLUDED
