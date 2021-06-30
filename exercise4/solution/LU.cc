#include <cassert>
#include <cmath>
#include <iostream>

#include "LU.hh"

namespace scprog {

void LU::compute (DenseMatrix const& A)
{
  // check for symmetric matrices
  assert(A.rows() == A.cols());
  std::size_t n = A.rows();

  // copy-assign the input matrix to the decomposition
  decomposition_ = A;

  for (std::size_t i = 0; i < n-1; ++i) {
    for (std::size_t k = i+1; k < n; ++k) {
      assert(std::abs(decomposition_(i,i)) > 1.e-10);
      decomposition_(k,i) = decomposition_(k,i) / decomposition_(i,i);
      for (std::size_t j = i+1; j < n; ++j)
        decomposition_(k,j) -= decomposition_(k,i) * decomposition_(i,j);
    }
  }
}


void LU::apply (Vector const& b, Vector& x) const
{
  assert(decomposition_.rows() == x.size());
  assert(decomposition_.cols() == b.size());

  // forward elimination
  Vector y{x.size()};
  for (std::size_t i = 0; i < y.size(); ++i) {
    Vector::value_type f = 0;
    for (std::size_t k = 0; k < i; ++k)
      f += decomposition_(i,k) * y[k];
    y[i] = b[i] - f;
  }

  // backward elimination
  for (std::size_t j = 0; j < x.size(); ++j) {
    std::size_t i = x.size()-j-1;
    Vector::value_type f = 0;
    for (std::size_t k = i+1; k < x.size(); ++k)
      f += decomposition_(i,k) * x[k];
    x[i] = (y[i] - f)/decomposition_(i,i);
  }
}


} // end namespace scprog
