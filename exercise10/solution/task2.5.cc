#include <iostream>
#include <tuple>

#include <benchmark/benchmark.h>

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

// a generic benchmark function
template <class Vec>
void benchmark_general (benchmark::State& state)
{
  Vec a{N, 1.0}, b{N, 2.0}, c{N, 3.0}; // create and initialize vectors of LARGE_SIZE
  bool pass = true;
  for (auto _ : state) {
    Vec sum = a + b + c;
    pass |= (sum[0] == 6.0);
  }
  assert(pass);
}


// create a benchmark for the expression-template based implementation
static void benchmark_expr (benchmark::State& state) {
  benchmark_general<scprog::Vector>(state);
}

// create a benchmark for the operator-overloading based implementation
static void benchmark_overload (benchmark::State& state) {
  benchmark_general<scprog::VectorOverloaded>(state);
}

// Register the functions as a benchmark
BENCHMARK(benchmark_expr);
BENCHMARK(benchmark_overload);

// Run the benchmark
BENCHMARK_MAIN();
