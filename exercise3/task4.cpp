#include <iostream>
#include <cassert>

struct DualNumber 
{
    // first is the "normal" entry, second the epsilon entry
    double first, second;
};

struct DualNumber add (DualNumber const num1, DualNumber const num2)
{
    // addition of two dual numbers
    DualNumber sum{};
    sum.first = num1.first + num2.first;
    sum.second = num1.second + num2.second;
    return sum;
}

struct DualNumber sub (DualNumber const num1, DualNumber const num2)
{
    // subtraction of two dual numbers
    DualNumber diff{};
    diff.first = num1.first - num2.first;
    diff.second = num1.second - num2.second;
    return diff;
}

struct DualNumber mul (DualNumber const num1, DualNumber const num2)
{
    // multiplication of two dual numbers
    DualNumber prod{};
    prod.first = num1.first * num2.first;
    prod.second = num1.first * num2.second + num1.second * num2.first;
    return prod;
}

struct DualNumber div (DualNumber const num1, DualNumber const num2)
{
    // division of two dual numbers; 
    // not defined if num2 equals zero or if the first value of num2 is zero 
    // but first value of num1 is not;
    // if num1.first and num2.first are zero and num2.second is not, quot.second is arbitrary
    DualNumber quot;
    if (num2.first != 0){
        quot.first = num1.first / num2.first;
        quot.second = (num1.second*num2.first - num1.first*num2.second)/(num2.first*num2.first);
        return quot;
    } else if (num2.second == 0 || num1.first != 0){
        std::cout << "No solution of division" << std::endl;
    } else{
        quot.first = num1.second / num2.second;
        quot.second = 0;
        return quot;
    }
}

struct DualNumber f (DualNumber const x)
{
    // function f from the task, 5*x^4 - 2*x^2 +7
    DualNumber help1{}, help2{}, help3{};
    help1 = mul(x,x);
    help2 = mul(help1, help1);
    help3 = add ( sub( mul({5,0}, help2), mul({2,0}, help1) ), {7,0});
    return help3;
}

struct DualNumber fDeriv (DualNumber const x)
{
    // first derivative of f
    DualNumber help1{}, help2{}, help3{};
    help1 = mul(x,x);
    help2 = mul(help1, x);
    help3 = sub( mul({20,0}, help2), mul({4,0}, x) ) ;
    return help3;
}


int main()
{
    // asserts the three statements eps*eps=0, 1*1=1, eps*1=1*eps, all other equations follow from these;
    // prints out f(x), f(a) and f'(a);
    // f(a) is the "normal" part of f(x), f'(a) is the "dual" part of f(x)
    DualNumber const one{1, 0};
    DualNumber const eps{0, 1};
    DualNumber const x{3, 1};
    DualNumber help1{}, help2{}, help3{};
    
    help1 = mul(eps, eps);
    assert (help1.first == 0 && help1.second == 0);

    help1 = mul(one, one);
    assert (help1.first == 1 && help1.second == 0);

    help1 = mul(one, eps);
    help2 = mul(eps, one);
    assert (help1.first == help2.first && help1.second == help2.second);

    help3 = f(x);
    std::cout << "f(x): " << help3.first << ", " << help3.second << std::endl;

    help3 = f({3,0});
    std::cout << "f(a): " << help3.first << ", " << help3.second << std::endl;

    help3 = fDeriv({3,0});
    std::cout << "f'(a): " << help3.first << ", " << help3.second << std::endl;
}