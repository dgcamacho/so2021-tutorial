#pragma once

#include <cassert>
#include <vector>

namespace scprog
{
  // forward declaration
  class Vector;

  class DenseMatrix
  {
  public:
    // The data type of the matrix entries
    using value_type = double;

    // The data type of the size and indices
    using size_type = std::size_t;

  public:
    // construct and initialize the matrix of size rows x cols
    DenseMatrix (size_type rows = 0, size_type cols = 0);

    // mutable access to the matrix entries
    value_type& operator() (size_type i, size_type j)
    {
      assert(i < rows_);
      assert(j < cols_);
      return data_[i*cols_ + j];
    }

    // const access to the matrix entries
    value_type const& operator() (size_type i, size_type j) const
    {
      assert(i < rows_);
      assert(j < cols_);
      return data_[i*cols_ + j];
    }

    // return the number of rows
    size_type rows () const
    {
      return rows_;
    }

    // return the number of columns
    size_type cols () const
    {
      return cols_;
    }

    // matrix-vector product y = A*x
    void mv (Vector const& x, Vector& y) const;

  private:
    std::size_t const rows_;
    std::size_t const cols_;
    std::vector<double> data_;
  };

} // end namespace scprog
