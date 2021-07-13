#pragma once

#include <utility>

namespace scprog {

// An arbitrary binary expression, acting on types at a certain index.
template <typename T, typename S, std::invocable<T, S, std::size_t> F>
class BinaryExpr {
private:
  T const& _a;
  S const& _b;
  F        _f;

public:
  using value_type = std::result_of<F(T, S, std::size_t)>::type;

  BinaryExpr(T const& a, S const& b, F f)
      : _a(a)
      , _b(b)
      , _f(f) {}

  // Get the result of the supplied function at the inde `i`.
  auto operator[](std::size_t i) const -> value_type { return _f(_a, _b, i); }

  auto size() const -> std::size_t { return _a.size(); }
};

template <typename T, typename S>
auto operator+(T const& a, S const& b) {
  return BinaryExpr{a, b, [](auto const& x, auto const& y, std::size_t i) {
                      return x[i] + y[i];
                    }};
}

template <typename T, typename S>
auto operator-(T const& a, S const& b) {
  return BinaryExpr{a, b, [](auto const& x, auto const& y, std::size_t i) {
                      return x[i] - y[i];
                    }};
}

// Return the matrix-vector product of the given values.
auto mat_vec(auto const& a, auto const& b) {
  return BinaryExpr{a, b, [](auto const& mat, auto const& vec, std::size_t i) {
                      return dot_product(mat[i], vec);
                    }};
}

} // namespace scprog
