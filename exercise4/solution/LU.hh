#pragma once

#include "DenseMatrix.hh"
#include "Vector.hh"

namespace scprog
{
  class LU
  {
  public:
    // decomposing the matrix m, without modifing it
    void compute (DenseMatrix const& A);

    // Solve the linear system A*x = b using the decomposed matrix
    void apply (Vector const& b, Vector& x) const;

  private:
    DenseMatrix decomposition_; // store the decomposition in this matrix
  };

} // end namespace scprog
