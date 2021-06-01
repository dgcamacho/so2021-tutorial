#pragma once

#include "DenseMatrix.hh"
#include "Vector.hh"

namespace scprog {
  class LU {
  public:
    LU();
    
    // calculate the LU-decomposition
    void compute(DenseMatrix const& m);
    
    // after the decomposition is calculated, solve the associated equation
    // compute needs to be called first, which is not internally enforced.
    void apply(Vector const& b, Vector& x);
    
    // print out the decomposition
    void print() const;

  private:
    DenseMatrix decomposition_; // store the decomposition in this matrix
  };

}
