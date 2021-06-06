#include "crs-matrix.hh"

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

auto main() -> int {
  // Example 1
  CRSMatrix<int> mat{4, 4, 4};
  Vector<int> y{1, 2, 3, 4};
  Vector<int> x(y.size());

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
  CRSMatrix<int>::CompressedMatrix com = mat.compress();
  com.mv(y, x);
  std::cout << x << std::endl;
}
