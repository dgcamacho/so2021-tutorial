#include <cmath>
#include <iostream>
#include <typeinfo>

struct X 
{
    int i;
    X(int j) : i(j) {}
    X operator+(int);
};

struct Y 
{
    int i;
    Y(X x) : i(x.i) {}
    Y operator+(X);
    operator int() { return i; }
};

inline X operator*(X, Y);
inline int f(X){ return 1; };

int main() 
{
    X x = 1;
    Y y = x;
    int i = 2;

    f(int(y));
    auto sum = y + y;
    std::cout << typeid(sum).name() << std::endl;
    106 + y;
}


