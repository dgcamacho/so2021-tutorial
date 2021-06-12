#include "CRS.h"
#include "Vector.hh"

using namespace scprog;

int main()
{
  CRSMatrix<double> A(3, 3, 2);
  A.add(0, 1, 7);
  A.add(2, 1, 3);
  A.add(2, 1, 2);
  A.add(1, 0, -3);
  A.compress();
  Vector V{3}, res{3};
  V[0] = 1; V[1] = 2; V[2] = -3;
  A.mv(V, res);
  return 0;
}
