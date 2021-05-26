#include <iostream>
#include <cmath>
#include <cassert>
#include <stdexcept>

struct DualNumber
{
    double a, b;

    DualNumber()
    {
        //Default intialisation
        a = 0.0, b = 0.0;
    }

    // I could pass an expression even if i used pass by reference why?
    DualNumber(double const x, double const y)
    {
        a = x, b = y;
    }

    void print()
    {
        if (b >= 0)
            std::cout << "The dual number is " << a << " + " << b << "ε" << std::endl;

        else
            std::cout << "The dual number is " << a << " - " << abs(b) << "ε" << std::endl;
    }

    void operator=(DualNumber d)
    {
        a = d.a, b = d.b;
    }

    DualNumber operator+(DualNumber const &d2)
    {
        DualNumber temp;
        temp.a = a + d2.a;
        temp.b = b + d2.b;

        return temp;
    }

    DualNumber operator-(DualNumber const &d2)
    {
        DualNumber temp;
        temp.a = a - d2.a;
        temp.b = b - d2.b;

        return temp;
    }

    DualNumber operator*(DualNumber const &d2)
    {
        DualNumber temp;
        temp.a = a * d2.a;
        temp.b = a * d2.b + b * d2.a;

        return temp;
    }

    DualNumber operator/(DualNumber const &d2)
    {
        DualNumber temp;

        if (d2.a != 0)
        {
            temp.a = a / d2.a;
            temp.b = b * d2.a - a * d2.b;
            temp.b /= pow(d2.a, 2);
        }
        else
            throw std::invalid_argument("divide by zero not possible");
        return temp;
    }

    bool operator==(DualNumber const &d2)
    {
        if (a == d2.a && b == d2.b)
            return 1;

        else
            return 0;
    }
};

using T = int;

DualNumber operator+(DualNumber d, T x)
{
    DualNumber temp;
    temp.a = d.a + x;
    temp.b = d.b;
    return temp;
}

DualNumber operator*(T x, DualNumber d)
{
    DualNumber temp;
    temp.a = x * d.a;
    temp.b = x * d.b;
    return temp;
}

DualNumber operator/(T x, DualNumber d)
{
    DualNumber temp;
    if (d.a != 0)
    {
        temp.a = 1.0 / d.a;
        temp.b = -d.b / pow(d.a, 2);
        temp = x * temp;
    }
    else
        throw std::invalid_argument("divide by zero not possible");
    return temp;
}

DualNumber pow(DualNumber d, int const &n)
{
    DualNumber temp(1, 1);
    for (int i = 0; i < n; i++)
    {
        temp = temp * d;
    }

    return temp;
}

DualNumber f(DualNumber d)
{
    return 5 * pow(d, 4) + (-2) * pow(d, 2) + 7;
}

DualNumber f_dash(DualNumber d)
{
    return 20 * pow(d, 3) + (-4) * d;
}

int main()
{
    //some small tests
    // float x=10, y=23;
    // DualNumber d1(x,y), d2(y,x);
    // d1.print();
    // d2.print();

    // DualNumber d3= d1+d2;
    // d3.print();

    // DualNumber d4= 3*d3;
    // d4.print();

    // DualNumber d5= d4+7;
    // d5.print();

    // DualNumber d6= d2/d1;
    // d6.print();

    // if i use const qualifier then i get this error
    //error: passing 'const DualNumber' as 'this' argument discards qualifiers [-fpermissive]
    // Is there any easy fix?
    DualNumber one(1, 0), eps(0, 1);

    assert(one * eps == eps * one);
    assert(one * eps == eps); //is there a way to combine these two?

    double a = 3, b = 1;
    auto d7 = f({a, b});
    auto d8 = f({a, 0});
    auto d9 = f_dash({a, 0});
    d7.print(), d8.print(), d9.print();

    assert(d7 == (d8 + b * (d9 * eps)));

    return 0;
}