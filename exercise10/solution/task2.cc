#include <iostream>
#include <tuple>

#include "Timer.hh"
#include "Vector.hh"
#include "VectorOverloaded.hh"

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

} // end namespace scprog


constexpr std::size_t N = 100000;
constexpr std::size_t MAX_ITER = 1000;

template <class Vec>
std::pair<bool,double> benchmark ()
{
  Vec a{N, 1.0}, b{N, 2.0}, c{N, 3.0}; // create and initialize vectors of LARGE_SIZE
  bool pass = true;
  scprog::Timer t;
  for (std::size_t i = 0; i < MAX_ITER; ++i) {
    Vec sum = a + b + c;
    pass |= (sum[0] == 6.0);
  }
  return {pass, t.elapsed()/MAX_ITER};
}



int main() {
  auto [pass1,timing1] = benchmark<scprog::Vector>();
  assert(pass1);

  auto [pass2,timing2] = benchmark<scprog::VectorOverloaded>();
  assert(pass2);

  std::cout << "Vector:           pass = " << pass1 << ", time = " << timing1 << std::endl;
  std::cout << "VectorOverloaded: pass = " << pass2 << ", time = " << timing2 << std::endl;

}
