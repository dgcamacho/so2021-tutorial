#pragma once

#include <vector>

namespace scprog {
  class Vector {
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

    // dot-product this with x
    value_type dot (Vector const& x) const;

    // add two vectors together
    Vector operator+(const Vector &b) const;

    // subtract two vectors
    Vector operator-(const Vector &b) const;

    // print this vector
    void print() const;

    // check if vector is almost 0
    bool is_null() const;

  private:
    std::vector<double> data_;
  };

}
