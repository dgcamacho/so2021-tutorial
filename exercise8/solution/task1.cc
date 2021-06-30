#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

namespace scprog
{
  struct Scale
  {
    double factor_;
    Scale (double factor) : factor_{factor} {}

    // scale the passed argument by the stored factor
    template <class T>
    void operator() (T& arg) const { arg *= factor_; }
  };

} // end namespace scprog


int main ()
{
  std::vector<double> vec{1.0,2.0,3.0,4.0,5.0,6.0};

  // scale the elements of the vector by factor 2
  std::for_each(vec.begin(), vec.end(), scprog::Scale{2.0});

  // print the vector to std::cout
  std::copy(vec.begin(), vec.end(), std::ostream_iterator<double>(std::cout, " "));
  std::cout << std::endl;
}