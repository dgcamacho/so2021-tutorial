#include "polynomial.hh"

#include <iostream>

using namespace lagrange;

auto main() -> int {
  Polynomial<double, 3> a{{1.0, 2.0, 3.0}};
  Polynomial<double, 3> c = a;
  Polynomial<double, 2> b = derivative(a);

  std::cout << "a: " << a << std::endl;
  std::cout << "b: " << b << std::endl;
  std::cout << "c: " << c << std::endl;
  c *= 2;
  std::cout << "c * 2: " << a << std::endl;
  std::cout << "a: " << a << std::endl;
  std::cout << "a + b: " << a + b << std::endl;
  std::cout << "a - b: " << a - b << std::endl;
  std::cout << "a * b: " << a * b << std::endl;
}
