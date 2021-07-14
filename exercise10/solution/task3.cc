#include "Vector.hh"

namespace scprog {

template <class S>
struct Scale {
  S factor;

  template <class T>
  auto operator() (T const& x) const { return factor*x; }
};

template <class A>
auto operator* (double factor, Expr<A> const& a)
{
  return UnaryExpr{Scale<double>{factor}, a};
}

template <class A>
auto operator* (Expr<A> const& a, double factor)
{
  return UnaryExpr{Scale<double>{factor}, a};
}

template <class A>
auto operator/ (Expr<A> const& a, double factor)
{
  return UnaryExpr{Scale<double>{1.0/factor}, a};
}

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

  Vector d{10}, e{10}, f{10};

  double alpha = 7.0;
  Vector t3 = alpha * (d + e) + f;
  Vector t4 = (d + e) / 2.0;
}
