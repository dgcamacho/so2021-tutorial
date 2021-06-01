#pragma once

#include <vector>

namespace scprog {
  // forward declaration
  class Vector;

  class DenseMatrix {
  public:
    // The data type of the matrix entries
    using value_type = double;

    // The data type of the size and indices
    using size_type = std::size_t;

  public:
    // construct and initialize the matrix of size rows x cols
    DenseMatrix (size_type rows, size_type cols);

    // mutable access to the matrix entries
    value_type& operator() (size_type i, size_type j);

    // const access to the matrix entries
    value_type const& operator() (size_type i, size_type j) const;

    // return the number of rows
    size_type rows () const;

    // return the number of columns
    size_type cols () const;

    // matrix-vector product y = A*x
    void mv (Vector const& x, Vector& y) const;

    // get a Vector representing the indexed row
    void row_by_index (size_type i, Vector& res) const;

    // print out this matrix
    void print() const;

  private:
    size_type rows_;
    size_type cols_;
    std::vector<value_type> data_;
  };

} // end namespace scprog
