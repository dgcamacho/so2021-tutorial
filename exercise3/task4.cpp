#import <iostream>
#import <cassert>

double static tolerance = 1e-8;

struct DualNumber {
    double a;
    double b;
};

DualNumber add(DualNumber &n, DualNumber &m){
    return DualNumber{n.a + m.a, n.b + m.b};
}

DualNumber sub(DualNumber &m, DualNumber &n){
    return DualNumber{m.a - n.a, m.b - n.b};
}

DualNumber mul(DualNumber &m, DualNumber &n){
    return DualNumber{m.a * n.a, m.a * n.b + m.b * n.a};
}

DualNumber div(DualNumber &m, DualNumber &n){
    assert(n.a > 1e-8);
    return DualNumber{m.a / n.a, (m.b * n.a - m.a * n.b) / (n.a * n.a)};
}

void compare_duals(DualNumber &m, DualNumber &n){ // todo allow for arbitrary number of input args
    assert(m.a - n.a < tolerance);
    assert(m.b - n.b < tolerance);
    std::cout << "Both numers match";
}

int main()
{
    DualNumber static one{1, 0};
    DualNumber static eps{0, 1};
    //Identities
    //i)
    auto one_x_eps = mul(one, eps);
    auto eps_x_one = mul(eps, one);
    compare_duals(one_x_eps, eps_x_one);
    //ii)
    auto first = mul(one, one_x_eps);
    auto second = &one_x_eps;

    return 0;
}
