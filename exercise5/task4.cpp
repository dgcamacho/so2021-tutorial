#include "CRS.h"

int main()
{
  scprog::CRSMatrix<double> A(4, 4, 2);
  A.add(0, 1, 7);
  A.add(2, 1, 3);
  A.add(2, 1, 5);
  A.add(1, 0, -3);
  A.compress();
  return 0;
}
