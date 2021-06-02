#include "DenseMatrix.hh"
#include "Vector.hh"
#include "LU.hh"

#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace scprog;

int main(void) {
  DenseMatrix A(3,3);
  A(0,0) =  2; A(0,1) = -1; A(0,2) =  0;
  A(1,0) = -1; A(1,1) =  2; A(1,2) = -1;
  A(2,0) =  0; A(2,1) = -1; A(2,2) =  2;
  
  Vector b(3), x(3);
  b[0] = 1; b[1] = 1; b[2] = 1;
  
  LU Adecomposition(A);
  Adecomposition.compute(A);
  Adecomposition.apply(b, x);
  
  Vector tmp(3);
  A.mv(x, tmp);
  tmp = b - tmp;
  
  Vector::value_type rNormSq{0};
  for( Vector::size_type i{0}; i < tmp.size(); i++ ) {
    rNormSq += tmp[i] * tmp[i];
  }
  
  std::cout << "Residual: " << std::sqrt(rNormSq) << std::endl;
  
  return EXIT_SUCCESS;
}
