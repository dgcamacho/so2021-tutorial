#include <cassert>
#include <iostream>
#include <iomanip>

#include "DenseMatrix.hh"
#include "Vector.hh"

namespace scprog {

DenseMatrix::DenseMatrix (size_type const rows, size_type const cols)
{
  rows_ = rows;
  cols_ = cols;
  data_ = std::vector<value_type>(rows*cols,0.0);
}


DenseMatrix::value_type& DenseMatrix::operator() (size_type const i, size_type const j)
{
  return data_[i*cols_+j];
}


DenseMatrix::value_type const& DenseMatrix::operator() (size_type const i, size_type const j) const
{
  return data_[i*cols_+j];
}


DenseMatrix::size_type DenseMatrix::rows () const
{
  return rows_;
}


DenseMatrix::size_type DenseMatrix::cols () const
{
  return cols_;
}


void DenseMatrix::mv (Vector const& x, Vector& y) const
{
  for (int i=0; i<rows_; ++i) {
    y[i] = 0;
    for (int j=0; j<cols_; ++j) {
      y[i] += (*this)(i,j) * x[j];
    }
  }
}

void DenseMatrix::print() {
  for (int i=0; i<rows_; ++i) {
    for (int j=0; j<cols_; ++j) {
      std::cout << std::setprecision(3) << std::setw(6) << (*this)(i,j)  << " ";
    }
    std::cout << std::endl;
  }
}

} // end namespace scprog
