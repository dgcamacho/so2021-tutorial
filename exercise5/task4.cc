#include "crs-matrix.hh"

#include <cmath>
#include <iostream>

using namespace scprog;

using OStream = std::ostream;

template <typename T>
auto operator<<(OStream& os, Vector<T> const& vec) -> OStream& {
  os << "[";
  for (std::size_t i = 0; i < vec.size() - 1; ++i) {
    os << vec[i] << ", ";
  }
  return os << vec[vec.size() - 1] << "]";
}

template <typename T>
auto two_norm(Vector<T> const& l, Vector<T> const& r) -> T {
  assert(l.size() == r.size());
  T res{0};
  for (decltype(l.size()) i = 0; i < l.size(); ++i) {
    res += l[i] * l[i] - r[i] * r[i];
  }
  return std::sqrt(res);
}

auto main() -> int {
  // Example 1
  CRSMatrix<double> mat{4, 4, 4};
  Vector<double> y{1, 2, 3, 4};
  Vector<double> x(y.size());

  // Fill matrix
  mat.set(0, 0, 1);
  mat.set(0, 2, 3);
  mat.set(1, 1, 2);
  mat.set(1, 3, -1);
  mat.set(2, 0, -4);
  mat.set(2, 1, -1);
  mat.set(2, 2, 1);
  mat.set(3, 0, 1);
  mat.set(3, 3, 3);

  // Compress and multiply
  CRSMatrix<double>::CompressedMatrix com = mat.compress();
  com.mv(y, x);
  Vector<double> exact{10, 0, -3, 13};
  std::cout << "Example 1 exact result: " << exact              << '\n'
            << "Computed result: "        << x                  << '\n'
            << "2-norm difference: "      << two_norm(exact, x) << "\n\n";

  // Example2: task 4 on sheet 6
  CRSMatrix<double> mat2{3, 3, 3};
  Vector<double> y2{1, 1, 1};
  Vector<double> x2(y2.size());

  // Insert from the back to test that
  mat2.set(0, 1, -1);
  mat2.set(0, 0, 2);
  mat2.set(1, 2, -1);
  mat2.set(1, 1, 2);
  mat2.set(1, 0, -1);
  mat2.set(2, 2, 2);
  mat2.set(2, 1, -1);

  CRSMatrix<double>::CompressedMatrix com2 = mat2.compress();
  com2.mv(y2, x2);
  Vector<double> exact2{1, 0, 1};
  std::cout << "Example 2 exact result: " << exact2               << '\n'
            << "Computed result: "        << x2                   << '\n'
            << "2-norm difference: "      << two_norm(exact2, x2) << '\n';
}
