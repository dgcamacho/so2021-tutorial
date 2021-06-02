#pragma once

#include <iostream>

#include "DenseMatrix.hh"
#include "Vector.hh"

namespace scprog
{
  class LU
  {
  public:
    LU(DenseMatrix const& m) : decomposition_(m.rows(),m.cols()) {};
  
    // decomposing the matrix m, without modifing it
    void compute (DenseMatrix const& m);

    void apply (Vector const& b, Vector& x) const;
    
    DenseMatrix const& get() const { return decomposition_; }

  private:
    DenseMatrix decomposition_; // store the decomposition in this matrix
  };
  
  std::ostream& operator<<(std::ostream& out, LU const& other);
} // end namespace scprog
