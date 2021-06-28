#pragma once

#include "common.hh"
#include "indexed-iter.hh"

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <ranges>
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

template <typename T, Size n, Size m>
auto operator*(Polynomial<T, n> const& p, Polynomial<T, m> const& q)
    -> Polynomial<T, n + m> {
  Polynomial<T, n + m> tmp(0.0);
  for (Size i = 0; i < n; ++i) {
    for (Size j = 0; j < m; ++j) {
      tmp._coeffs[i + j] += p[i] * q[j];
    }
  }
  return tmp;
}

template <typename T, Size n, Size m, std::invocable<T, T> Op>
auto apply_pointwise(Polynomial<T, n> const& p, Polynomial<T, m> const& q,
                     Op op) -> Polynomial<T, std::max(n, m)> {
  Polynomial<T, std::max(n, m)> tmp(0.0);
  auto const& range = std::ranges::iota_view{0ul, std::max(n, m)};
  std::transform(range.begin(), range.end(), tmp.begin(),
                 [&p, &q, op](Size ix) {
                   return (n > m) ? ((ix < m) ? op(p[ix], q[ix]) : p[ix])
                                  : ((ix < n) ? op(q[ix], p[ix]) : q[ix]);
                 });
  return tmp;
}

template <typename T, Size n, Size m>
auto operator+(Polynomial<T, n> const& p, Polynomial<T, m> const& q)
    -> Polynomial<T, std::max(n, m)> {
  return apply_pointwise(p, q, std::plus<T>());
}

template <typename T, Size n, Size m>
auto operator-(Polynomial<T, n> const& p, Polynomial<T, m> const& q)
    -> Polynomial<T, std::max(n, m)> {
  return apply_pointwise(p, q, std::minus<T>());
}

template <typename T, Size n>
auto operator*(Polynomial<T, n> const& p, T alpha) -> Polynomial<T, n> {
  Polynomial<T, n> tmp{p};
  tmp *= alpha;
  return tmp;
}

template <typename T, Size n>
auto derivative(Polynomial<T, n> const& p) -> Polynomial<T, n - 1> {
  Polynomial<T, n - 1> tmp(0.0);
  auto const& range = std::ranges::iota_view{0ul, n - 1};
  std::transform(range.begin(), range.end(), tmp.begin(),
                 [&p](Size ix) { return p[ix + 1] * (ix + 1); });
  return tmp;
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
