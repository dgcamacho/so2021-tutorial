#include <iostream>

#include "DenseMatrix.hh"

using namespace scprog;

auto main() -> int {
  Vec<double> a{1, 2};
  Vec<double> b{4, 5};

  DenseMatrix<double> m{2, 2, {10, 20, 30, 40}};
  Vec<double>         c{a + m * (a - b)};

  for (auto el : c)
    std::cout << el << " ";
}
