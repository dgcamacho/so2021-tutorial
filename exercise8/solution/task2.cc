#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <numeric>
#include <vector>

void print (std::string name, std::vector<int> const& v)
{
  std::cout << name << ":";
  for (int vi : v)
    std::cout << ' ' << vi;
  std::cout << std::endl;
}

int main ()
{
  std::srand(std::time(nullptr));

  // create a vector with 10 elements
  std::vector<int> vec(10,0);

  // fill the vector with random values
  std::generate(vec.begin(), vec.end(), []{ return std::rand() % 10; });
  print("vec", vec);

  // Copies the elements in the range, defined by [first, last), to another range. Only copies the
  // elements for which the predicate pred returns true
  std::vector<int> result1;
  std::copy_if(vec.begin(), vec.end(), std::back_inserter(result1),
    [](int v) { return v > 4; });
  print("result1", result1);

  // Copies elements from the range [first, last), to another range, omitting the elements which
  // satisfy specific criteria.
  std::vector<int> result2;
  std::remove_copy_if(vec.begin(), vec.end(), std::back_inserter(result2),
    [](int v) { return v == 2; });
  print("result2", result2);

  // Applies the given function to a range and stores the result in another range, keeping the
  // original elements order.
  std::vector<int> result3(vec.size());
  std::transform(vec.begin(), vec.end(), result3.begin(), [](int v) { return v * 2; });
  print("result3", result3);

  // with C++17
  int result4a = std::transform_reduce(vec.begin(), vec.end(), 0,
    [](int a, int b) { return std::max(a,b); },
    [](int a) { return std::abs(a); });
  std::cout << "result4a: " << result4a << std::endl;

  // with C++14
  int result4b = std::accumulate(vec.begin(), vec.end(), 0,
    [](int a, int b) { return std::max(std::abs(a), std::abs(b)); });
  std::cout << "result4b: " << result4b << std::endl;

  std::vector<int> result5;
  std::copy(vec.rbegin(), vec.rend(), std::back_inserter(result5));
  print("result5", result5);
}