#include <cassert>
#include <iostream>

double const tolerance = 1e-8;

struct DualNumber {
    double a;
    double b;

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

DualNumber fPrime(DualNumber x)
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
    auto const one_x_eps = one * eps;

    //Test assertions
    assert(one == one);
    assert(!(zero == one));

    //Check identities
    //i)
    assert(one_x_eps == eps * one);
    assert(one_x_eps == eps);
    assert(eps * one == eps);

    //ii)
    assert(one * one_x_eps == one_x_eps);
    assert(one * one_x_eps == (one * one) * eps);
    assert(one * one_x_eps == eps);
    assert(one_x_eps == (one * one) * eps);
    assert((one * one) * eps == eps);

    //iii)
    assert(one * (eps * eps) == one * zero);
    assert(one * (eps * eps) == zero);
    assert(one * (eps * eps) == eps * eps);
    assert(one * (eps * eps) == one_x_eps * eps);
    assert(one * zero == zero);
    assert(one * zero == eps * eps);
    assert(one * zero == one_x_eps * eps);
    assert(zero == eps * eps);
    assert(zero == one_x_eps * eps);
    assert(eps * eps == one_x_eps * eps);

    DualNumber const a{3, 1};
    auto f_a = f(a);
    auto f_prime_a = fPrime(a);
    std::cout << "Original dual number a: ";
    a.print();
    std::cout << "Polynomial 5x^4 - 2x^2 + 7 evaluated with a. f(a)= ";
    f_a.print();
    std::cout << "Derivative of polynomial evaluated with a. f'(a)= ";
    f_prime_a.print();
    return 0;
}
