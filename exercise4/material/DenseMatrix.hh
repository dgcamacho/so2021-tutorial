#pragma once

#include <iostream>
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
    DenseMatrix (size_type rows, size_type cols);
    DenseMatrix( DenseMatrix const& other );

    // mutable access to the matrix entries
    value_type& operator() (size_type i, size_type j);

    // const access to the matrix entries
    value_type const& operator() (size_type i, size_type j) const;
    
    DenseMatrix& operator*=(DenseMatrix const&);
    DenseMatrix& operator=(DenseMatrix const&);

    // return the number of rows
    size_type rows () const;

    // return the number of columns
    size_type cols () const;

    // matrix-vector product y = A*x
    void mv (Vector const& x, Vector& y) const;

  private:
    std::size_t rows_;
    std::size_t cols_;
    std::vector<double> data_;
  };
  
  DenseMatrix operator*(DenseMatrix const& lhs, DenseMatrix const& rhs);
  std::ostream& operator<<(std::ostream& out, DenseMatrix const& other);

} // end namespace scprog
