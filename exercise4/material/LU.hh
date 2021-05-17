#pragma once

#include "DenseMatrix.hh"
#include "Vector.hh"

namespace scprog
{
  class LU
  {
  public:
    // decomposing the matrix m, without modifing it
    void compute (DenseMatrix const& m)
    {
      /*...*/
    }

    void apply (Vector const& b, Vector& x) const
    {
      /*...*/
    }

  private:
    DenseMatrix decomposition_; // store the decomposition in this matrix
  };

} // end namespace scprog
