#include <cassert>
#include <iostream>

double const tolerance = 1e-12; // Value for absolute error in equality comparisons

struct DualNumber {
    /// Dual number consisting of real part 'a' and epsilon part 'b', which fulfils the property b*b=0.
    double a; // real part
    double b; // eps part

    DualNumber operator+(DualNumber dual) const{
        return DualNumber{this->a + dual.a, this->b + dual.b};
    };
 
    DualNumber operator-(DualNumber dual) const{
        return DualNumber{this->a - dual.a, this->b - dual.b};
    };

    DualNumber operator*(DualNumber dual) const{
        return DualNumber{this->a * dual.a, this->a * dual.b + this->b * dual.a};
    };
    DualNumber operator/(DualNumber dual) const{
        assert(dual.a > tolerance);
        return DualNumber{this->a / dual.a, (this->b * dual.a - this->a * dual.b) / (dual.a * dual.a)};
    };

    bool operator==(DualNumber dual) const{
        return (std::abs(this->a - dual.a) < tolerance) && (std::abs(this->b - dual.b) < tolerance);
    }
    void print() const{
        std::cout << "Dual number " << this->a << " + " << this->b << " eps" << std::endl;
    }
};

DualNumber f(DualNumber x)
{
    DualNumber five{5,0};
    DualNumber two{2,0};
    DualNumber seven{7,0};
    return five * x * x * x * x - (two * x * x) + seven;
}

DualNumber f_prime(DualNumber x)
{
    DualNumber twenty{20, 0};
    DualNumber four{4,0};
    return twenty * x * x * x - (four * x);
}

int main()
{
    DualNumber const zero{0, 0};
    DualNumber const one{1, 0};
    DualNumber const eps{0, 1};

    //Test assertions
    assert(one == one);
    assert(!(zero == one));
    assert(eps * eps == zero); // Condition for dual numbers

    //Check identities
    //i)
    assert(one * eps == eps * one);
    assert(one * eps == eps);
    assert(eps * one == eps);

    //ii)
    assert(one * (one * eps) == one * eps);
    assert(one * (one * eps) == (one * one) * eps);
    assert(one * (one * eps) == eps);
    assert(one * eps == (one * one) * eps);
    assert((one * one) * eps == eps);

    //iii)
    assert(one * (eps * eps) == one * zero);
    assert(one * (eps * eps) == zero);
    assert(one * (eps * eps) == eps * eps);
    assert(one * (eps * eps) == one * eps * eps);
    assert(one * zero == zero);
    assert(one * zero == eps * eps);
    assert(one * zero == one * eps * eps);
    assert(zero == eps * eps);
    assert(zero == (one * eps) * eps);
    assert(eps * eps == (one * eps) * eps);

    // Function & derivative
    DualNumber const d{3, 1};

    std::cout << "Original dual number d: ";
    d.print();
    std::cout << "Polynomial 5x^4 - 2x^2 + 7 evaluated with a. f(d)= ";
    f(d).print();
    std::cout << "Derivative of polynomial evaluated with a. f'(d)= ";
    f_prime(d).print();
    return 0;
}
