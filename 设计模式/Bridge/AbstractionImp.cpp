#include "AbstractionImp.hpp"
#include <iostream>
using namespace std;

AbstractionImp::AbstractionImp()
{

}
AbstractionImp::~AbstractionImp()
{

}
void AbstractionImp::Operation()
{
    cout<<"AbstractionImp...imp..."<<endl;
}

SubAbstractionImpA::SubAbstractionImpA()
{

}
SubAbstractionImpA::~SubAbstractionImpA()
{

}
void SubAbstractionImpA::Operation()
{
    cout<<"SubAbstractionImpA...imp..."<<endl;
}

SubAbstractionImpB::SubAbstractionImpB()
{

}
SubAbstractionImpB::~SubAbstractionImpB()
{

}
void SubAbstractionImpB::Operation()
{
    cout<<"SubAbstractionImpB...imp..."<<endl;
}
