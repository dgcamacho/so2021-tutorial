#pragma once

#include "Util.hh"

namespace scprog {

  // Forward declarations.
  class Vector;
  class DenseMatrix;

  class LU {
  public:
    // Decompose the matrix m, without modifing it.
    auto compute (DenseMatrix const& m) -> void;

    /**
     * Compute A · x = b, where A = LU.  Solve the system by forwards
     * and backwards application of LU factors; i.e., solve L · y = b
     * and U · x = y.  The given vectors b and x must be of the same
     * size as the (square) matrix A.
     */
    auto apply (Vector const& b, Vector& x) const -> void;

  private:
    DenseMatrix _decomposition; // store the decomposition in this matrix

    // Convenience operators.
    auto operator()(Size const i, Size const j) -> Value& {
      return _decomposition(i, j);
    }
    auto operator()(Size const i, Size const j) const -> Value const& {
      return _decomposition(i, j);
    }
  };

} // end namespace scprog
