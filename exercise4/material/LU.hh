#pragma once

#include "Util.hh"

namespace scprog {

  // Forward declarations.
  class Vector;
  class DenseMatrix;

  class LU {
  public:
    // Decomposing the matrix m, without modifing it.
    auto compute (DenseMatrix const& m) -> void {
      /*...*/
    }

    auto const apply (Vector const& b, Vector& x) -> void {
      /*...*/
    }

  private:
    DenseMatrix _decomposition; // store the decomposition in this matrix
  };

} // end namespace scprog
