#include <iostream>
struct CircleStruct
{
    int x, y;
    double radius;
};
class CircleClass
{
public:
    CircleClass(int x, int y, double radius)
    : mX(x), mY(y), mRadius(radius) {}
private:
    int mX, mY;
    double mRadius;
};

int main(int argc, char const *argv[])
{
    CircleStruct a1={1,2,3.0};
    CircleClass b1={1,2,3.0}; //合法的
    return 0;
}