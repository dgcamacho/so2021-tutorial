#pragma once

#include "DenseMatrix.hh"
#include "Vector.hh"

namespace scprog
{
  class LU
  {
  public:
      using size_t = std::size_t;
      using real_t = double;
  public:
    // decomposing the matrix m, without modifing it
    void compute(DenseMatrix const& m);
    
    // swapping rows to allow pivoting steps
    void swap_rows(size_t k, size_t l);

    // solve the actual lgs with a given rhs-vector b
    void apply(Vector const& b, Vector& x) const;

  private:
    DenseMatrix decomposition_; // store the decomposition in this matrix
    DenseMatrix perturbation_;  // store the perturbation steps
    bool swapped_ = 0;          // stores whether rows where swapped
  };
}
