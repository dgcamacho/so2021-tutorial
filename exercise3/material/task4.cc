#include <iostream>
#include <cmath>
#include <cassert>

struct DualNumber {
    double a;
    double b;
};


DualNumber operator+(DualNumber const &x_1, DualNumber const &x_2)
{
    return {x_1.a + x_2.a, x_1.b + x_2.b};
}

DualNumber operator-(DualNumber const &x_1, DualNumber const &x_2)
{
    return {x_1.a - x_2.a, x_1.b - x_2.b};
}

DualNumber operator*(DualNumber const &x_1, DualNumber const &x_2)
{
    return {x_1.a*x_2.a, x_1.a*x_2.b + x_1.b*x_2.a};
}

DualNumber operator/(DualNumber const &x_1, DualNumber const &x_2)
{
    return {x_1.a/x_2.a, (x_1.b*x_2.a - x_1.a*x_2.b)/(x_2.a*x_2.a)};
}

bool operator==(DualNumber const &x_1, DualNumber const &x_2)
{
    return ((x_1.a == x_2.a) && (x_1.b == x_2.b));
}

int main(){

    DualNumber x_tilde{3.0, 1.0};
    return 0;
}
