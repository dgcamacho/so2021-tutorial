#include <algorithm>
#include <array>
#include <cmath>
#include <ctime>
#include <iostream>
#include <limits>

////////////////////////////////////////////////////////////////////////
// Types

// The C++ stdlib (from what I have seen) uses `size_t` for size
// parameters and so that was adopted here.

template <size_t n>
using Mat = std::array<std::array<double, n>, n>;

template <size_t n>
using Vec = std::array<double, n>;

////////////////////////////////////////////////////////////////////////
// Operations on matrices and vectors

/**
 * Matrix-vector multiplication by taking the vector to be an
 * (n × 1)-dimensional matrix.
 */
template <size_t n>
auto operator*(Mat<n> const& mat, Vec<n> const& vec) -> Vec<n> {
  Vec<n> res;
  for (size_t row = 0; row < n; ++row) {
    double tmp = 0;
    for (size_t col = 0; col < n; ++col) {
      tmp += mat.at(row).at(col) * vec.at(col);
    }
    res.at(row) = tmp;
  }
  return res;
}

/// Component-wise left multiplication of a scalar with a vector.
template <size_t n>
auto operator*(double const& scalar, Vec<n> const& vec) -> Vec<n> {
  Vec<n> ret;
  for (size_t i = 0; i < n; ++i) {
    ret.at(i) = scalar * vec.at(i);
  }
  return ret;
}

/// Subtract two vectors from each other component-wise.
template <size_t n>
auto operator-(Vec<n> const& lvec, Vec<n> const& rvec) -> Vec<n> {
  Vec<n> ret;
  for (size_t i = 0; i < n; ++i) {
    ret.at(i) = lvec.at(i) - rvec.at(i);
  }
  return ret;
}

/**
 * The dot product between two vectors.
 *
 * Note that this is not an operator due to the fact that, in comparison
 * to matrix-vector multiplication, there is not just one obvious way to
 * multiply two vectors together (one may well say that element-wise
 * multiplication should get the operator spot).
 */
template <size_t n>
auto dot_product(Vec<n> const& lvec, Vec<n> const& rvec) -> double {
  double res = 0;
  for (size_t i = 0; i < n; ++i) {
    res += lvec.at(i) * rvec.at(i);
  }
  return res;
}

/// Compute the Euclidean norm of a vector.
template <size_t n>
auto euclidean_norm(Vec<n> const& vec) -> double {
  return sqrt(dot_product(vec, vec));
}

////////////////////////////////////////////////////////////////////////
// The actual iteration code

/**
 * Generate a random vector such that it is _not_ in the kernel of the
 * given matrix.
 */
template <size_t n>
auto find_initial_value(Mat<n> const& mat) -> Vec<n> {
  // Generate a random vector of length `n`
  auto random_vec = []() {
    Vec<n> vec;
    for (size_t i = 0; i < n; ++i) {
      vec.at(i) = std::rand();
    }
    return vec;
  };
  // Check if a `double` is _almost_ 0.
  auto is_zero = [](double const& x) {
    return std::abs(x) <= 2 * std::numeric_limits<double>::epsilon();
  };

  while (true) {
    Vec<n> r0 = random_vec();
    // Only return the vector if it is not in the kernel of `mat`
    Vec<n> m  = mat * r0;
    if (!std::all_of(m.begin(), m.end(), is_zero))
      return r0;
  }
}

/// Compute the Rayleigh quotient for a given matrix-vector pair.
template <size_t n>
auto rayleigh_quotient(Mat<n> const& mat, Vec<n> const& r) -> double {
  return dot_product(r, mat * r) / dot_product(r, r);
}

/**
 * Via the power method, approximate the eigenvector r⁽ᵏ⁾ for the given
 * matrix.
 *
 * In every step, print the Rayleigh quotient of the current iteration.
 */
template <size_t n>
auto power_method(Mat<n> const& mat, int const k) -> Vec<n> {
  Vec<n> r = find_initial_value(mat);
  std::cout << "The Rayleigh quotient for the initial vector is: "
            << rayleigh_quotient(mat, r) << std::endl;
  for (int i = 1; i <= k; ++i) {
    Vec<n> ar   = mat * r;             // A · r
    double norm = euclidean_norm(ar);  // ∥A · r∥
    for (size_t j = 0; j < n; ++j) {   // r⁽ⁱ⁾
      r.at(j) = ar.at(j) / norm;
    }
    std::cout << "The Rayleigh quotient in iteration " << i
              << " is: " << rayleigh_quotient(mat, r)
              << std::endl;
  }
  return r;
}

////////////////////////////////////////////////////////////////////////
// Main

/**
 * Given a matrix A, an eigenvalue σ, and the approximated eigenvector
 * to that eigenvalue r, compute the Euclidean norm of A · r - σ · r.
 */
template <size_t n>
auto test (Mat<n> const& mat, Vec<n> const& r, double const& sigma) -> double {
  return euclidean_norm(mat * r - sigma * r);
}

auto main() -> int {
  // Seed `rand()` with the current system time, as advised by the
  // documentation.
  std::srand(std::time(0));

  Mat<3> matB = {{{3,  0,  0}, {0,   1,  0}, {0, 0, 1}}};
  Vec<3> vecB = power_method(matB, 20);
  std::cout << "B · r - σ · r in the Euclidean norm: "
            << test(matB, vecB, 3)
            << std::endl << std::endl;

  Mat<3> matC = {{{4, -1, -1}, {0.5, 2, -2}, {0, 0, 1}}};
  Vec<3> vecC = power_method(matC, 20);
  std::cout << "C · r - σ · r in the Euclidean norm: "
            << test(matC, vecC, 0.5 * (6 + sqrt(2)))
            << std::endl;
}
