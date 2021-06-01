#include <cassert>

#include "DenseMatrix.hh"
#include "Vector.hh"

namespace scprog {

DenseMatrix::DenseMatrix (size_type const rows, size_type const cols){
  this->rows_ = rows;
  this->cols_ = cols;
  this->data_ = std::vector<value_type>(rows_ * cols_, 0);
}


// standard-access operators
DenseMatrix::value_type& DenseMatrix::operator() (size_type const i, size_type const j){
  return this->data_[i * cols_ + j];
}

DenseMatrix::value_type const& DenseMatrix::operator() (size_type const i, size_type const j) const{
  return this->data_[i * cols_ + j];
}

// size information
DenseMatrix::size_type DenseMatrix::rows () const{
  return this->rows_;
}

DenseMatrix::size_type DenseMatrix::cols () const{
  return this->cols_;
}


// get the indexed row as a Vector
void DenseMatrix::row_by_index (size_type i, Vector& res) const {
    for (int j = 0; j < res.size(); ++j)
    {
        res[j] = (*this)(i, j);
    }
}


// calculate a matrix-vector-product
void DenseMatrix::mv (Vector const& x, Vector& y) const{
    for (int i = 0; i < this->rows_; ++i){
        for (int j = 0; j < this->cols_; j++) {
          y[i] += (*this)(i, j) * x[j];
        }
    }
}

// print out the matrix
void DenseMatrix::print() const {
  Vector res = Vector(this->cols_);
  std::cout << "[";
  for (int i = 0; i < this->rows_; ++i){
    this->row_by_index(i, res);
    res.print();
  }
  std::cout << "]\n";
}

}
