#include "polynomial.hh"

#include <iostream>

using namespace lagrange;

auto main() -> int {
  Polynomial<double, 3> a{{1.0, 2.0, 3.0}};

  std::cout << "a: " << a << std::endl;
  a *= 2;
  std::cout << "a * 2: " << a << std::endl;
}
