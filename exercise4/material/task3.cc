#include "DenseMatrix.cc"
#include "LU.cc"
#include "Vector.cc"

#include <iostream>

auto main() -> int {
  using namespace scprog;

  DenseMatrix mat(3, 3, { 2, -1,  0,
                         -1,  2, -1,
                          0, -1,  2});
  Vector b{1, 1, 1};
  Vector x(b.size());

  // Compute LU decomposition and solve the linear system
  LU lu_mat(mat);
  lu_mat.apply(b, x);
  std::cout << "[x₁, x₂, x₃] = " << x << std::endl;

  // Compute residual and compare
  Vector y(x.size());
  mat.mv(x, y);        // Stores result in `y`
  std::cout << "Residual b - A · x = " << b - y << std::endl;
}
