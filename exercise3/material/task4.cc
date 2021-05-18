#include <cassert>
#include <cmath>
#include <iostream>

// Define the datatype DualNumber, which defines a number of the structure 
// x = a + b*eps, where a and b are real numbers and eps is a number 
// satisfying the identity eps^2 = 0. 
struct DualNumber {
    double a;
    double b;
    double tol_equality = 1e-8; //used tolerance for the equality operator

    //simply adds two dualnumbers
    DualNumber operator+(DualNumber const that) const
    {
        return {this->a + that.a, this->b + that.b};
    }

    //simply subtracts two dualnumbers
    DualNumber operator-(DualNumber const that) const
    {
        return {this->a - that.a, this->b - that.b};
    }
    
    //returns the product of two dual numbers, which results from the identity
    //which eps has to satisfy.
    DualNumber operator*(DualNumber const that) const
    {
        return {this->a * that.a, this->a * that.b + this->b * that.a};
    }

    //returns the division of two dual numbers, which results from the identity
    //which eps has to satisfy.
    DualNumber operator/(DualNumber const that) const
    {
        return {this->a / that.a, (this->b * that.a - this->a * that.b) /
                                (that.a * that.a)};
    }

    //evaluates component-wise the equality of two dualnumbers. 
    bool operator==(DualNumber const that) const 
    {
        return ((std::abs(this->a - that.a) <= this->tol_equality) && 
                (std::abs(this->b - that.b) <= this->tol_equality));
    }

    //prints the given dualnumber 
    void printDual()
    {
        std::cout << this->a << " + eps*" << 
                     this->b << std::endl;
    }
};

//overloads operator+, so that one can add a dualnumber to a double, so that
//one does not has to create a new dualnumber for every used double.
DualNumber operator+(double const val, DualNumber const dual)
{
    DualNumber val_dual{val, 0.0};
    return val_dual + dual;
}

//overloads operator- for substraction of dualnumber and double.
DualNumber operator-(double const val, DualNumber const dual)
{
    DualNumber val_dual{val, 0.0};
    return val_dual - dual;
}

//overloads operator* for multiplication of dualnumber and double.
DualNumber operator*(double const val, DualNumber const dual)
{
    DualNumber val_dual{val, 0.0};
    return val_dual * dual;
}

//overloads operator/ for division of dualnumber and double, where the
//dualnumber is in the denominator. 
DualNumber operator/(double const val, DualNumber const dual)
{
    DualNumber val_dual{val, 0.0};
    return val_dual / dual;
}

//returns the result of the polynomial f(x) = c + bx^2 + ax^4 for a given
//dualnumber x.
DualNumber Polynomial(DualNumber const x, double const a, double const b,
                      double const c)
{
    return c + (b * x * x) + (a * x * x * x * x);
}

//returns the derivative f'(x) of f(x) = c + bx^2 + ax^4, which is 
//f'(x) = 2bx + 4ax^3 evaluated for a given dualnumber x.
DualNumber DerivativeofPolynomial(DualNumber const x, double const a, 
                                  double const b)
{
    return (2*b*x) + (4*a*x*x*x);
}


//function evaluates whether the implemented structure of a dualnumber is able
//to satisfy the basic identities of dualnumbers.
void testIdentities()
{
    DualNumber one{1.0, 0.0};   
    DualNumber eps{0.0, 1.0};
    DualNumber zero{0.0, 0.0};

    //checks the identity 1*eps = eps*one = eps
    assert((one * eps == eps * one) && (eps * one == eps));
    //checks the identity 1*(1*eps) = 1*eps = (1*1)*eps = eps
    assert((one * (one * eps) == one * eps) && 
           (one * eps == (one * one) * eps) &&
           ((one * one) * eps == eps));
    //checks the identity 1*(eps*eps) = 0*eps = 0 = eps*eps = (1*eps)*eps
    assert((one * (eps * eps) == zero * eps) &&
           (zero * eps == zero) &&
           (zero == eps * eps) &&
           (eps * eps == (one * eps) * eps));
}

int main(){

    testIdentities();
    DualNumber x_d{3.0, 1.0};
    std::cout << "For the given dualnumber x = 3 + eps*1, we get the value:"
              << std::endl;
    Polynomial(x_d, 5.0, -2.0, 7.0).printDual();
    std::cout << "For this dualnumber, the derivative of the polynomial is:"
              << std::endl;
    DerivativeofPolynomial(x_d, 5.0, -2.0).printDual();
    return 0;
}
