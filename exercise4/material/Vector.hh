#pragma once

#include <vector>

namespace scprog
{
  class Vector
  {
  public:
    // The data type of the matrix entries
    using value_type = double;

    // The data type of the size and indices
    using size_type = std::size_t;

  public:
    // construct and initialize the matrix of size rows x cols
    Vector (size_type size);

    // mutable access to the matrix entries
    value_type& operator[] (size_type i);

    // const access to the matrix entries
    value_type const& operator[] (size_type i) const;

    // return the number of vector entries
    size_type size () const;

  private:
    std::vector<double> data_;
  };

} // end namespace scprog
