#pragma once

#include "DenseMatrix.hh"
#include "Vector.hh"

namespace scprog
{
  class LU
  {
  public:
    // decomposing the matrix m, without modifing it
    void compute (DenseMatrix const& m);

    // solve the system Ax = b for x applying the decomposition
    void apply (Vector const& b, Vector& x) const;

    // print the decomposition matrices
    void printLU () {
      DenseMatrix L = decomposition_;
      DenseMatrix U = decomposition_;
      L(0,0) = 1;
      for (int i = 1; i < decomposition_.rows(); ++i) {
        L(i,i) = 1.0;
        for (int j = 0; j < i; ++j) {
          U(i,j) = 0.0;
          L(j,i) = 0.0;
        }
      }
      std::cout << "\nL =\n";
      L.print();
      std::cout << "\nU =\n";
      U.print();
    };

  private:
    DenseMatrix decomposition_; // store the decomposition in this matrix
  };

} // end namespace scprog
