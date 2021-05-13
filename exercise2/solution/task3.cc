#include <iostream>
#include <limits>
#include <type_traits>

int main()
{
  double x1 = 42.0f;
  std::cout << "x1 = " << x1 << std::endl;
  static_assert(std::is_same_v<float, decltype(42.0f)>);

  float x2 = 1e-50;
  std::cout << "x2 = " << x2 << std::endl;
  static_assert(std::is_same_v<double, decltype(1e-50)>);

  double x3 = 1/2;
  std::cout << "x3 = " << x3 << std::endl;
  static_assert(std::is_same_v<int, decltype(1/2)>);

  double x4 = 1.0/2;
  std::cout << "x4 = " << x4 << std::endl;
  static_assert(std::is_same_v<double, decltype(1.0/2)>);

  int x5 = -3ul + 4;
  std::cout << "x5 = " << x5 << std::endl;
  static_assert(std::is_same_v<unsigned long, decltype(-3ul + 4)>);
}