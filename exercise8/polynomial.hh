#pragma once

#include "common.hh"

#include <cassert>

namespace lagrange {

template <typename T, Size n> class Polynomial {
private:
  Arr<T, n> _coeffs; // in ascending order: [a₀, a₁, ..., a₍ₙ₋₁₎]

public:
  using Value = T;

  // Initialize a polynomial with all coefficients having this value.
  explicit Polynomial(Value val) : _coeffs{val} {}

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

  // Multiply two polynomials.
  template <typename S, Size k, Size m>
  auto friend operator*(Polynomial<S, k> const& p, Polynomial<S, m> const& q)
      -> Polynomial<S, k + m>;
};

///////////////////////////////////////////////////////////////////////
// Arithmetic

/**
 * Apply a binary operation pointwise to two polynomials.  The
 * function takes the arguments `(S a, S b)`, where `a` is from `p`
 * and `b` is from `q`.  If one polynomial is longer than the other,
 * then copy the remainder to the new polynomial without applying the
 * function.
 */
template <typename T, Size n, Size m, std::invocable<T, T> Op>
auto apply_pointwise(Polynomial<T, n> const& p, Polynomial<T, m> const& q,
                     Op op) -> Polynomial<T, std::max(n, m)>;

// Add two polynomials.
template <typename T, Size n, Size m>
auto operator+(Polynomial<T, n> const& p, Polynomial<T, m> const& q)
    -> Polynomial<T, std::max(n, m)>;

// Subtract two polynomials.
template <typename T, Size n, Size m>
auto operator-(Polynomial<T, n> const& p, Polynomial<T, m> const& q)
    -> Polynomial<T, std::max(n, m)>;

// Multiply a polynomial with a scalar.
template <typename T, Size n>
auto operator*(Polynomial<T, n> const& p, T alpha) -> Polynomial<T, n>;

///////////////////////////////////////////////////////////////////////
// Transformations

// Calculate the formal derivative of the given polynomial.
template <typename T, Size n>
auto derivative(Polynomial<T, n> const& p) -> Polynomial<T, n - 1>;

///////////////////////////////////////////////////////////////////////
// Pretty-printing

// Pretty-print a polynomial in its standard form.
template <typename T, Size n>
auto operator<<(OStream& os, Polynomial<T, n> const& p) -> OStream&;

} // namespace lagrange

#include "polynomial.impl.hh"
