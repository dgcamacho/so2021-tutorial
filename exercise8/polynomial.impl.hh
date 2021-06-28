#pragma once

#include "common.hh"

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <numeric>
#include <string>

namespace lagrange {

template <typename T, Size n>
auto Polynomial<T, n>::operator()(Value x) -> Value {
  return std::accumulate(IndexedIter(this->begin() + 1),
                         IndexedIter(this->end()), _coeffs[0],
                         [&x](Value acc, auto el) {
                           return acc + el.first * std::pow(x, el.second + 1);
                         });
}

template <typename T, Size n>
auto Polynomial<T, n>::operator*=(Value alpha) -> void {
  std::transform(this->begin(), this->end(), this->begin(),
                 [&alpha](Value el) { return el * alpha; });
}

template <typename T, Size n>
auto operator<<(OStream& os, Polynomial<T, n> const& p) -> OStream& {
  auto pretty_print = [&os](T val, std::string end) {
    (val == 0) ? os : os << ((val > 0) ? " + " : " - ") << std::abs(val) << end;
  };
  // Special handling for a₀ and a₁x.
  (p[0] == 0) ? os : os << p[0];
  pretty_print(p[1], "x");
  // Higher-order terms all have the same style.
  for (Size i = 2; i < n; ++i) {
    pretty_print(p[i], "x^" + std::to_string(i));
  }
  return os;
}

} // namespace lagrange
