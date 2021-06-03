#include <algorithm>
#include <cassert>
#include <iomanip>
#include <iostream>


#include "DenseMatrix.hh"
#include "Vector.hh"

namespace scprog {

DenseMatrix::DenseMatrix (size_type const rows, size_type const cols) : rows_(rows), cols_(cols),  data_(rows * cols, 0) {}
DenseMatrix::DenseMatrix (DenseMatrix const& other) : rows_(other.rows()), cols_(other.cols()), data_(other.data_) {}

DenseMatrix& DenseMatrix::operator=(DenseMatrix const& other) {
  data_ = other.data_;
  return *this;
}


DenseMatrix::value_type& DenseMatrix::operator() (size_type const i, size_type const j)
{
    assert( i * cols() + j < rows() * cols() );
    return data_[i * cols() + j];
}


DenseMatrix::value_type const& DenseMatrix::operator() (size_type const i, size_type const j) const
{
    assert( i * cols() + j < rows() * cols() );
    return data_[i * cols() + j];
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
    using SizeType = DenseMatrix::size_type;

    assert( y.size() == cols() );
    for( SizeType i{0}; i < rows(); i++ ) {
        y[i] = 0;
        for( SizeType j{0}; j < cols(); j++ ) {
            y[i] += x[j] * (*this)(i,j);
        }
    }
}

DenseMatrix& DenseMatrix::operator *=(DenseMatrix const& other) {
  using SizeType = DenseMatrix::size_type;
  
  assert( this->cols() == other.rows() );
  
  DenseMatrix old{*this};
  
  std::fill( data_.begin(), data_.end(), DenseMatrix::value_type{0} );
  
  for( SizeType i{0}; i < rows(); i++ ) {
    for( SizeType k{0}; k < other.cols(); k++ ) {
      for( SizeType j{0}; j < cols(); j++ ) {
        (*this)(i,j) += old(i,k) * other(k,j);
      }
    }
  }
  
  return *this;
}

DenseMatrix operator*(DenseMatrix const& lhs, DenseMatrix const& rhs) {
  return DenseMatrix{lhs} *= rhs;
}

std::ostream& operator<<(std::ostream& out, DenseMatrix const& other) {
  using SizeType = DenseMatrix::size_type;
  
  for( SizeType i{0}; i < other.rows(); i++ ) {
    for( SizeType j{0}; j < other.cols(); j++ ) {
      out << std::setw(10) << other(i,j) << ' ';
    }
    out << std::endl;
  }
  
  return out;
}

} // end namespace scprog
