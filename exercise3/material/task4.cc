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

DualNumber operator+(double const real, DualNumber const &x)
{
    return {real + x.a, 0.0 + x.b};
}

DualNumber operator+(DualNumber const &x, double const real)
{
    return {x.a + real, 0.0 + x.b};
}

DualNumber operator-(DualNumber const &x_1, DualNumber const &x_2)
{
    return {x_1.a - x_2.a, x_1.b - x_2.b};
}

DualNumber operator-(double const real, DualNumber const &x)
{
    return {x.a - real, x.b - 0.0};
}

DualNumber operator*(DualNumber const &x_1, DualNumber const &x_2)
{
    return {x_1.a*x_2.a, x_1.a*x_2.b + x_1.b*x_2.a};
}

DualNumber operator*(double const real, DualNumber const &x)
{
    return {real*x.a, real*x.b};
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
    DualNumber f = 5.0*x_tilde*x_tilde*x_tilde*x_tilde 
                   - 2.0*x_tilde*x_tilde + 7.0;
    std::cout << f.a << " " << f.b << std::endl;
    return 0;
}
