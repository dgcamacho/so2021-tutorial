#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>

namespace scprog
{
  struct DualNumber
  {
    double re;
    double ep;
  };

  DualNumber operator+ (DualNumber const& a, DualNumber const& b)
  {
    return DualNumber{.re=a.re+b.re, .ep=a.ep+b.ep};
  }

  DualNumber operator- (DualNumber const& a, DualNumber const& b)
  {
    return DualNumber{.re=a.re-b.re, .ep=a.ep-b.ep};
  }

  DualNumber operator* (DualNumber const& a, DualNumber const& b)
  {
    return DualNumber{.re=a.re*b.re, .ep=(a.re*b.ep + a.ep*b.re)};
  }

  DualNumber operator/ (DualNumber const& a, DualNumber const& b)
  {
    assert(std::abs(b.re) > 1.e-10);
    return DualNumber{.re=a.re/b.re, .ep=(a.ep*b.re - a.re*b.ep)/(b.re*b.re)};
  }

  DualNumber pow (DualNumber const& x, int n)
  {
    assert(n >= 0);
    switch (n) {
      case 0:  return DualNumber{1.0,0.0};
      case 1:  return x;
      case 2:  return x*x;
      default: return pow(x,n-1) * x;
    }
  }

  bool almost_equal (double x, double y, int ulp = 2)
  {
    return std::abs(x-y) <= std::numeric_limits<double>::epsilon() * ulp * std::abs(x+y)
        || std::abs(x-y) <  std::numeric_limits<double>::min();
  }

  bool almost_equal (DualNumber x, DualNumber y, int ulp = 2)
  {
    return almost_equal(x.re,y.re,ulp) && almost_equal(x.ep,y.ep,ulp);
  }

  bool test1 ()
  {
    DualNumber const _0{0.0,0.0};
    DualNumber const _1{1.0,0.0};
    DualNumber const _eps{0.0,1.0};

    bool pass1 = almost_equal( _1 * _eps, _eps );
    bool pass2 = almost_equal( _eps * _1, _eps );
    bool pass3 = almost_equal( _eps * _eps, _0 );
    bool pass4 = almost_equal( _1 * _1, _1 );

    return pass1 && pass2 && pass3 && pass4;
  }

  bool test2 ()
  {
    DualNumber const _2{2.0,0.0};
    DualNumber const _4{4.0,0.0};
    DualNumber const _5{5.0,0.0};
    DualNumber const _7{7.0,0.0};
    DualNumber const _20{20.0,0.0};

    DualNumber _x{3.0,1.0};
    DualNumber _a{3.0,0.0};

    auto f = _5 * pow(_x,4) - _2 * pow(_x,2) + _7;
    auto df= _20* pow(_a,3) - _4 * _a;

    std::cout << "f(x)  = {" << f.re << ", " << f.ep << "}" << std::endl;
    std::cout << "f'(a) = {" << df.re << ", " << df.ep << "}" << std::endl;

    return almost_equal(f.ep, df.re);
  }
}

int main()
{
  using namespace scprog;

  bool pass1 = test1();
  bool pass2 = test2();

  return pass1 && pass2 ? 0 : 42;
}