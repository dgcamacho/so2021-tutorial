#pragma once

#include "Vector.hh"
#include "DenseMatrix.hh"

namespace scprog
{
  class LU
  {
  public:
    // decomposing the matrix m, without modifing it
    void compute (DenseMatrix const& m)
    {
      // TODO: implement me!
    }

    void apply (Vector const& b, Vector& x) const
    {
      // TODO: implement me!
    }

  private:
    DenseMatrix decomposition_; // store the decomposition in this matrix
  };

} // end namespace scprog
