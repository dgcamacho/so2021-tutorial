#include <iostream>
#include <cmath>
#include <cassert>

// 1. data type for dual numbers
struct DualNumber
{
    double a;
    double b;
};

// 2. Operations
/*
DualNumber add (DualNumber x, DualNumber y) {
    DualNumber result;
    result.a = x.a + y.a;
    result.b = x.b + y.b;
    return result;
}

DualNumber sub (DualNumber x, DualNumber y) {
    DualNumber result;
    result.a = x.a - y.a;
    result.b = x.b - y.b;
    return result;
}

DualNumber mul (DualNumber x, DualNumber y) {
    DualNumber result;
    result.a = x.a * y.a;
    result.b = x.a * y.b + x.b * y.a;
    return result;
}

DualNumber mul(double alpha, DualNumber x) {
    DualNumber result;
    result.a = alpha * x.a;
    result.b = alpha * x.b;
    return result;
}

DualNumber div (DualNumber x, DualNumber y) {
    DualNumber result;
    result.a = x.a / y.a;
    result.b = (x.b * y.a - x.a * y.b) / (y.a * y.a);
    return result;
}
*/

// 5. operators 
DualNumber operator+ (DualNumber x, DualNumber y) {
    DualNumber result;
    result.a = x.a + y.a;
    result.b = x.b + y.b;
    return result;
}

DualNumber operator- (DualNumber x, DualNumber y) {
    DualNumber result;
    result.a = x.a - y.a;
    result.b = x.b - y.b;
    return result;
}

DualNumber operator* (DualNumber x, DualNumber y) {
    DualNumber result;
    result.a = x.a * y.a;
    result.b = x.a * y.b + x.b * y.a;
    return result;
}

DualNumber operator* (double alpha, DualNumber x) {
    DualNumber result;
    result.a = alpha * x.a;
    result.b = alpha * x.b;
    return result;
}


void print (DualNumber x, std::string message = "") {
    std::cout << message << "(" << x.a << ", " << x.b << ")\n";
}

bool equal (DualNumber x, DualNumber y) {
    return std::abs(x.a - y.a) < std::numeric_limits<double>::epsilon() && std::abs(x.b - y.b) < std::numeric_limits<double>::epsilon();
}

DualNumber f (DualNumber x) {
    DualNumber result;
    result = (5 * ((x*x)*(x*x))) - (2 * (x*x));
    result.a += 7;
    return result;
}

double f (double x) {
    double result;
    result = 5*x*x*x*x - 2*x*x + 7;
    return result;
}

DualNumber deriv_f (DualNumber x) {
    DualNumber result;
    result = (20 * ((x*x)*x)) - (4*x);
    return result;
}

double deriv_f (double x) {
    double result;
    result = 20*x*x*x - 4*x;
    return result;
}

int main() {
    // 3. 
    // define constants one and eps (and zero)
    const DualNumber one = {1,0};
    const DualNumber eps = {0,1};
    const DualNumber zero = {0,0};

    // test the given identities
    /*
    std::cout << "1st equation: " << (equal(one * eps, eps * one) && equal(one * eps, eps)) << std::endl;
    std::cout << "2nd equation: " << (equal(one * (one * eps), eps) && equal(eps,  one * eps) && equal(eps,  (one * one) * eps)) << std::endl;
    std::cout << "3rd equation: " << (equal(one * (eps * eps), one * zero) && equal(one * zero, zero) && equal((1 * eps) * eps, zero) && equal(eps * eps, zero)) << std::endl;
    */

    assert((equal(one * eps, eps * one) && equal(one * eps, eps)));
    assert(equal(one * (one * eps), eps) && equal(eps,  one * eps) && equal(eps,  (one * one) * eps));
    assert(equal(one * (eps * eps), one * zero) && equal(one * zero, zero) && equal((1 * eps) * eps, zero) && equal(eps * eps, zero));
    
    // 4. evaluate the function f at x
    DualNumber x = {3,1};
    double a = 3.0;
    print(x, "x = ");
    print(f(x), "f(x) = ");
    std::cout << "f(a) = " << f(a) << std::endl;
    std::cout << "f'(a) = " << deriv_f(a) << std::endl;
    std::cout << "First component of f(x) is equal to f(a)." << std::endl; 
    std::cout << "Second component of f(x) is equal to f'(a)." << std::endl;
}