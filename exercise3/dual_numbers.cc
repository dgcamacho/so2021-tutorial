#include <iostream>
#include <cmath>

struct DualNumber
{
    double a;
    double b;
};

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


void print (DualNumber x) {
    std::cout << "(" << x.a << ", " << x.b << ")";
}

bool equal (DualNumber x, DualNumber y) {
    return x.a == y.a && x.b == y.b;
}

DualNumber f (DualNumber x) {
    DualNumber result;
    result = (5 * ((x*x)*(x*x))) - (2 * (x*x));
    result.a += 7;
    return result;
}

DualNumber deriv_f (DualNumber x) {
    DualNumber result;
    result = (20 * ((x*x)*x)) - (4*x);
    return result;
}

int main() {
    // 3. 
    // define constants one and eps (and zero)
    const DualNumber one = {1,0};
    const DualNumber eps = {0,1};
    const DualNumber zero = {0,0};

    print(one);
    print(eps);

    // test the given identities
    std::cout << "First equation: " << (equal(one * eps, eps * one) && equal(one * eps, eps)) << std::endl;
    
    std::cout << "Second equation: " << (equal(one * (one * eps), eps) && equal(eps,  one * eps) && equal(eps,  (one * one) * eps)) << std::endl;
    
    std::cout << "Third equation: " << (equal(one * (eps * eps), one * zero) && equal(one * zero, zero) && equal((1 * eps) * eps, zero) && equal(eps * eps, zero)) << std::endl;

    // 4.
    DualNumber x = {3,1};

    std::cout << "f("; print(x); std::cout << ") = ";
    print(f(x));
    std::cout << "\n";
    std::cout << "f'("; print(x); std::cout << ") = ";
    print(deriv_f(x));    
    std::cout << "\n";
    


}