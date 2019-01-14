#include <iostream>
#include <iterator>

using namespace std;

int main()
{
    double v1,v2;
    cout<<"please insert two values: ";
    
    istream_iterator<double> eos; //end of stream iterator
    istream_iterator<double> iter(cin);
    if(iter != eos)
        v1 = *iter;
    
    ++iter;
    if(iter != eos)
        v2 = *iter;
    
    cout<<v1<<"   "<<v2<<endl;
    
    return 0;
}