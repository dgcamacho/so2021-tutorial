#pragma once

#include "common.hh"

#include <cassert>

namespace lagrange {

template <typename T, Size n> class Polynomial {
private:
  Arr<T, n> _coeffs; // in ascending order: [a₀, a₁, ..., a₍ₙ₋₁₎]

public:
  using Value = T;

  /**
   * Construct a polynomial from an array; the array will be interpreted
   * as a list of coefficients aᵢ, such that the full polynomial may be
   * represented as a₀ + a₁ · x + ⋯ + a₍ₙ₋₁₎ · x⁽ⁿ⁻¹⁾.
   */
  explicit Polynomial(Arr<T, n> const& arr) : _coeffs(arr) {}

  // Read-only access to a polynomial coefficient; value must be in range.
  auto operator[](Size i) const -> Value const& {
    assert(i >= 0 && i < n);
    return _coeffs[i];
  }

  // Evaluate a polynomial at the given value.
  auto operator()(Value x) -> Value;

  // Scale the coefficients of a polynomial by the given value.
  auto operator*=(Value alpha) -> void;

  auto begin() { return _coeffs.begin(); }
  auto begin() const { return _coeffs.begin(); }
  auto end() { return _coeffs.end(); }
  auto end() const { return _coeffs.end(); }
};

// Pretty-print a polynomial in its standard form.
template <typename T, Size n>
auto operator<<(OStream& os, Polynomial<T, n> const& p) -> OStream&;

} // namespace lagrange

#include "polynomial.impl.hh"
