#include <string>
#include "Subject.hpp"
using namespace std;

class Observer
{
public:
    Observer();
    ~Observer();
    void update(State st);
    void printInfo();
private:
    State _st;
};
