#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <optional>
#include <vector>

////////////////////////////////////////////////////////////////////////
// PascalCase aliases for non-primitive types

namespace PascalCaseAliases {
  template<typename T>
  using Optional = std::optional<T>;

  template<typename T>
  using Vector = std::vector<T>;

  using OStream = std::ostream;
}

using namespace PascalCaseAliases;

////////////////////////////////////////////////////////////////////////
// Float equality (from the lecture)

auto almost_equal(double const x, double const y) -> bool {
  using std::abs;
  using std::numeric_limits;
  return abs(x - y) <= numeric_limits<double>::epsilon() * abs(x + y) * 2
      || abs(x - y) <  numeric_limits<double>::min();
}

////////////////////////////////////////////////////////////////////////
// Dual numbers

/**
 * Simple type for representing a dual number; i.e., a number of the
 * form x ≔ a + bε, where ε² ≡ 0.
 *
 * Much like in the case of complex numbers, we shall refer to `a` as
 * the _real part_ and to `b` as the _epsilon part_ of `x`.
 */
struct DualNumber {
  double re;
  double ep;
};

/// Dual numbers can only be compared for equality as precisely as
/// floating points can.
auto almost_equal(DualNumber const& l, DualNumber const& r) -> bool {
  return almost_equal(l.re, r.re) && almost_equal(l.ep, r.ep);
}

/// Pretty-print a dual number as "a + bε".
auto operator<<(OStream& os, DualNumber const& dn) -> OStream& {
  os << dn.re << " + " << dn.ep << "ε";
  return os;
}

/// Add two dual numbers component-wise.
auto operator+(DualNumber const& l, DualNumber const& r) -> DualNumber {
  return {.re = l.re + r.re, .ep = l.ep + r.ep};
}

/// Add a dual number and a double; the latter is treated as a dual
/// number without an epsilon component.
auto operator+(DualNumber const& l, double const r) -> DualNumber {
  return {.re = l.re + r, .ep = l.ep};
}

/// Subtract two dual numbers component-wise.
auto operator-(DualNumber const& l, DualNumber const& r) -> DualNumber {
  return {.re = l.re - r.re, .ep = l.ep - r.ep};
}

/**
 * Multiply two dual numbers.  The multiplication is according to the
 * usual matrix multiplication, as we may represent an element `a + bε`
 * as an upper triangular matrix of the form {{a, b}, {0, a}}.
 */
auto operator*(DualNumber const& l, DualNumber const& r) -> DualNumber {
  return {.re = l.re * r.re, .ep = l.re * r.ep + l.ep * r.re};
}

/// Multiply a real number and a dual number; the former is treated as a
/// dual number without an epsilon component.
auto operator*(double const l, DualNumber const& r) -> DualNumber {
  return {.re = l * r.re, .ep = l * r.ep};
}

/// A wrapper for divisible dual numbers.
struct DivisibleDN {
private:
  DualNumber unwrap;

public:
  /// Safe, implicit, conversion to a dual number is always possible.
  operator DualNumber() const { return unwrap; };

  /// Try to construct a divisible dual number.
  auto static const make(DualNumber const& dn) -> Optional<DivisibleDN> {
    // Constructors are strict so there is no nice `? :` pattern here.
    if (almost_equal(dn.ep * dn.ep, 0)) {
      return std::nullopt;
    }
    DivisibleDN res; res.unwrap = dn;
    return std::optional(res);
  }
};

/**
 * Safe division of dual numbers.
 *
 * This works analogous to complex division, in that we multiply the
 * numerator and denominator with the conjugate of the denominator and
 * then cancel the epsilon terms.
 */
auto operator/(DualNumber const& num, DivisibleDN const& ddn) -> DualNumber {
  DualNumber den = ddn;
  return {.re = num.re / den.re,
          .ep = (num.ep * den.re - num.re * den.ep) / (den.re * den.re)};
}

////////////////////////////////////////////////////////////////////////
// Main

/// The polynomial `f` we want to look at, over some arbitrary ring of
/// numbers.
template <typename T>
auto f(T const& x) -> T {
  return (5 * x * x * x * x) - (2 * x * x) + 7;
}

/// The derivative of `f` if it is first specialized to an idealized
/// function ℝ → ℝ and then differentiated with respect to `x`.
auto f_prime(double const x) -> double {
  return 4 * x * (5 * x * x - 1);
}

/**
 * Check if every element in the given list is equal to the supplied
 * reference value.
 *
 * This is technically an incorrect implementation, as it assumes that
 * `almost_equal` is transitive, which is not true in general.  However,
 * a "correct" implementation would either (wrongly) use `==` or be
 * O(n²) in the size of the vector (because we actually do need to
 * compare every element to every other element), which seems much worse
 * than this (perhaps mild) assumption.
 */
auto all_equal_to(DualNumber const& ref, Vector<DualNumber> const& vec) -> bool {
 return std::all_of(vec.begin(),
                    vec.end(),
                    [&ref](DualNumber y){ return almost_equal(ref, y); });
}

auto main() -> int {
  DualNumber const one {.re = 1, .ep = 0};
  DualNumber const zero{.re = 0, .ep = 0};
  DualNumber const eps {.re = 0, .ep = 1};

  assert(all_equal_to(eps, {one * eps, eps * one}));
  assert(all_equal_to(eps, {one * (one * eps), one * eps, (one * one) * eps}));
  assert(all_equal_to(
    zero, {one * (eps * eps), one * zero, eps * eps, (one * eps) * eps}));

  double     const a{3};
  DualNumber const x{.re = a, .ep = 1};

  assert(almost_equal(f(x).re, f(a)));
  assert(almost_equal(f(x).ep, f_prime(a)));

  Optional<DivisibleDN> const d = DivisibleDN::make(x);
  if (d.has_value()) {
    std::cout << "(" << x << ") / (" << d.value() << ") = "
              << x / d.value() << "\n\n";
  }

  std::cout << "An interesting observation is that, given any real polynomial "
            << "f, we have f(a + bε) ≡ f(a) + (b · f'(a))ε.\n"
            << "For our chosen f and x ≔ a + bε = " << x << ", we get: \n\n"
            << "  f(x)  = " << f(x)       <<  "\n"
            << "  f(a)  = " << f(a)       <<  "\n"
            << "  f'(a) = " << f_prime(a) << ".\n";
}
