#include <cassert>

#include <iostream>

#include "LU.hh"

#include "DenseMatrix.hh"

namespace scprog {
  
void LU::compute(DenseMatrix const& m) {
  using SizeType = DenseMatrix::size_type;
  
  assert( m.cols() == m.rows() );
  
  DenseMatrix U{m},
              Identity{m.cols(), m.cols()};
  
  for( SizeType i{0}; i < m.cols(); i++ ) {
    Identity(i,i) = 1.0;
  }
  
  auto L{Identity};
  
  for( SizeType n{0}; n < m.cols() - 1; n++ ) {
    auto Ln{Identity}, LnInv{Identity};
    
    for( SizeType i{n+1}; i < m.cols(); i++ ) {
      Ln(i,n) = -U(i,n) / U(n,n);
      LnInv(i,n) = -Ln(i,n);
    }
    
    U = Ln * U;
    L *= LnInv;
  }
  
  decomposition_ = DenseMatrix{U};
  for( SizeType i{1}; i < U.rows(); i++ ) {
    for( SizeType j{0}; j < i; j++ ) {
      decomposition_(i,j) = L(i,j);
    }
  }
}

void LU::apply (Vector const& b, Vector& x) const {
  using SizeType = Vector::size_type;
  
  Vector y(x.size());
  
  // solve Ly = b
  for( SizeType i{0}; i < x.size(); i++ ) {
    y[i] = b[i];
    for( SizeType j{0}; j < i; j++ ) {
      y[i] -= y[j] * decomposition_(i,j);
    }
  }
  
  // solve Ux = y
  for( int i = x.size()-1; i >= 0; i-- ) {
    x[i] = y[i];
    for( int j = x.size() - 1; j > i; j-- ) {
      x[i] -= x[j] * decomposition_(i,j);
    }
    x[i] /= decomposition_(i,i);
  }
}

std::ostream& operator<<(std::ostream& out, LU const& other) {
    return out << other.get();
  }
  
}
