#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>

namespace scprog
{
  struct DualNumber
  {
    double const re;
    double const ep;

    DualNumber (double re = 0, double ep = 0)
      : re(re), ep(ep) {}
  };


  std::ostream& operator<< (std::ostream& out, DualNumber const& x)
  {
    return out << '{' << x.re << ", " << x.ep << '}';
  }

  DualNumber operator+ (DualNumber const& a, DualNumber const& b)
  {
    return {a.re+b.re, a.ep+b.ep};
  }

  DualNumber operator- (DualNumber const& a, DualNumber const& b)
  {
    return {a.re-b.re, a.ep-b.ep};
  }

  DualNumber operator* (DualNumber const& a, DualNumber const& b)
  {
    return {a.re*b.re, a.re*b.ep + a.ep*b.re};
  }

  DualNumber operator/ (DualNumber const& a, DualNumber const& b)
  {
    assert(std::abs(b.re) > std::numeric_limits<double>::epsilon());
    return {a.re/b.re, (a.ep*b.re - a.re*b.ep)/(b.re*b.re)};
  }

  DualNumber pow (DualNumber const& x, int n)
  {
    assert(n >= 0);
    switch (n) {
      case 0:  return 1;
      case 1:  return x;
      case 2:  return x*x;
      default: return pow(x,n-1) * x;
    }
  }

  DualNumber cos (DualNumber const& x)
  {
    using std::sin; using std::cos;
    return {cos(x.re), -x.ep*sin(x.re)};
  }

  DualNumber sin (DualNumber const& x)
  {
    using std::sin; using std::cos;
    return {sin(x.re), x.ep*cos(x.re)};
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
    DualNumber const _eps{0.0,1.0};

    bool pass1 = almost_equal( 1 * _eps, _eps );
    bool pass2 = almost_equal( _eps * 1, _eps );
    bool pass3 = almost_equal( _eps * _eps, 0 );

    return pass1 && pass2 && pass3;
  }

  bool test2 ()
  {
    DualNumber _x{3.0,1.0};
    DualNumber _a{3.0};

    auto f = 5 * pow(_x,4) - 2 * pow(_x,2) + 7;
    auto df= 20* pow(_a,3) - 4 * _a;

    std::cout << "f(x)  = " << f << std::endl;
    std::cout << "f'(a) = " << df << std::endl;

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