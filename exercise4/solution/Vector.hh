#pragma once

#include <cassert>
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
    explicit Vector (size_type size = 0);

    // mutable access to the matrix entries
    value_type& operator[] (size_type i)
    {
      assert(i < size());
      return data_[i];
    }

    // const access to the matrix entries
    value_type const& operator[] (size_type i) const
    {
      assert(i < size());
      return data_[i];
    }

    // return the number of vector entries
    size_type size () const
    {
      return data_.size();
    }

  private:
    std::vector<double> data_;
  };

} // end namespace scprog
