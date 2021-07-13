#pragma once

#include <cassert>
#include <vector>

#include "ExpressionTemplates.hh"

namespace scprog {

// A thin wrapper around `std::vector`, in order to be able to use the
// class in expression templates.
template <typename T>
struct Vec : public std::vector<T> {
  using Super      = std::vector<T>;
  using value_type = T;

  // Evaluate an expression and construct a vector from it.
  template <typename A, typename B, typename F>
  Vec(BinaryExpr<A, B, F> const& expr)
      : Vec(expr.size()) {
    for (size_t i = 0; i < this->size(); ++i)
      (*this)[i] = expr[i];
  }

  using Super::vector;
};

// Return the dot product of the two given vectors.
template <typename T, typename S>
auto dot_product(T lhs, S rhs) -> T::value_type {
  assert(lhs.size() == rhs.size());
  typename T::value_type res = 0;
  for (size_t i = 0; i < lhs.size(); ++i) {
    res += lhs[i] * rhs[i];
  }
  return res;
}

} // namespace scprog
