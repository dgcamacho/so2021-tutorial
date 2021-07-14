#include <iostream>
#include <vector>

#include "integer_range.hh" // -> integer_range
#include "task3.hh"

int main()
{
  using namespace scprog;

  std::vector<double> vec = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};

  std::cout << "vector:\n";
  for (auto x : map([](auto x) { return 2*x; }, vec))
    std::cout << x << "\n";

  std::cout << "integer_range:\n";
  for (auto x : map([](auto x) { return x%7; }, range(10)))
    std::cout << x << "\n";
}
