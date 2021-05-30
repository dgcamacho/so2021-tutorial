#pragma once

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
    
    // default-constructor
    DenseMatrix ();

    // mutable access to the matrix entries
    value_type& operator() (size_type i, size_type j);

    // const access to the matrix entries
    value_type const& operator() (size_type i, size_type j) const;
    
    // set a value of the matrix
    void setValue (size_type const i, size_type const j, value_type value);
    
    // initialize the matrix with given values
    void initialize (std::vector<value_type> const& allValues);

    // return the number of rows
    size_type rows () const;

    // return the number of columns
    size_type cols () const;

    // matrix-vector product y = A*x
    void mv (Vector const& x, Vector& y) const;
    
    // print matrix values
    void print () const;

  private:
    std::size_t rows_;
    std::size_t cols_;
    std::vector<double> data_;
  };

} // end namespace scprog
