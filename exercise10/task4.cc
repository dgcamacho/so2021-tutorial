#include <iostream>

// #include "CRSMatrix.hh"
#include "DenseMatrix.hh"

using namespace scprog;

auto main() -> int {
  Vec<double> a{1, 2};
  Vec<double> b{4, 5};

  DenseMatrix<double> m{2, 2, {10, 20, 30, 40}};
  Vec<double>         c{a + m * (a - b)};

  for (auto el : c)
    std::cout << el << " ";

  // CRSMatrix<double> m1{4, 4, 4};
  // Vector<double>    y{1, 2, 3, 4};
  // Vector<double>    x{5, 6, 7, 8};
  // m1.set(0, 0, 1);
  // m1.set(0, 2, 3);
  // m1.set(1, 1, 2);
  // m1.set(1, 3, -1);
  // m1.set(2, 0, -4);
  // m1.set(2, 1, -1);
  // m1.set(2, 2, 1);
  // m1.set(3, 0, 1);
  // m1.set(3, 3, 3);
  // CRSMatrix<double>::CompressedMatrix m2 = m1.compress();
  // Vec<double>         z{y + m2 * (x - y)};
}
