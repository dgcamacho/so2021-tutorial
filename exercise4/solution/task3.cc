#include <iostream>

#include "DenseMatrix.hh"
#include "LU.hh"
#include "Vector.hh"

int main()
{
  using namespace scprog;

  DenseMatrix A{3,3};
  A(0,0) = 2; A(0,1) =-1;
  A(1,0) =-1; A(1,1) = 2; A(1,2) =-1;
              A(2,1) =-1; A(2,2) = 2;

  Vector b{3};
  b[0] = 1; b[1] = 1; b[2] = 1;

  LU lu_solver;
  lu_solver.compute(A);

  Vector x{3};
  lu_solver.apply(b, x);

  std::cout << "x = [" << x[0] << ", " << x[1] << ", " << x[2] << "]" << std::endl;

  A.mv(x, b);
  std::cout << "b = [" << b[0] << ", " << b[1] << ", " << b[2] << "]" << std::endl;

}