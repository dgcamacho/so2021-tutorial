#include "Vector.hh"

namespace scprog {

struct Plus {
  template <class T1, class T2>
  auto operator() (T1 const& x, T2 const& y) const { return x + y; }
};

template <class A, class B>
auto operator+ (Expr<A> const& a, Expr<B> const& b)
{
  return BinaryExpr{Plus{}, a, b};
}


struct Minus {
  template <class T1, class T2>
  auto operator() (T1 const& x, T2 const& y) const { return x + y; }
};

template <class A, class B>
auto operator- (Expr<A> const& a, Expr<B> const& b)
{
  return BinaryExpr{Minus{}, a, b};
}

} // end namespace scprog

int main ()
{
  using namespace scprog;

  Vector a{10}, b{10}, c{10};

  Vector sum = a + b + c;
  Vector dif = a - a;
}
