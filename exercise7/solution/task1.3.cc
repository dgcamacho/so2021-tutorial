#include <functional> // -> std::less

namespace scprog
{
  struct Rational
  {
    double numerator;
    double denominator;
  };

  template <typename T, typename Compare = std::less<T> >
  T min (T a, T b, Compare less = Compare{})
  {
    return less(a, b) ? a : b;
  }

} // end namespace scprog

template <class T>
bool greater (T a, T b)
{
  return a > b;
}

struct Less
{
  bool operator() (scprog::Rational const& a, scprog::Rational const& b) const
  {
    // requires that denominator > 0
    return a.numerator * b.denominator < b.numerator * a.denominator;
  }
};

int main ()
{
  double x0 = scprog::min(1.0, 2.0); // => 1.0
  double x1 = scprog::min(1.0, 2.0, [](double a, double b) { return a > b; }); // => 2.0
  int x2 = scprog::min(1, 2, greater<int>); // => 2

  scprog::Rational r = scprog::min(scprog::Rational{-1,2}, scprog::Rational{4,2}, Less{});
}
