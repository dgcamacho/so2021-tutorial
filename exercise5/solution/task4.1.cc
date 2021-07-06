#include <iostream>

#include "CRSMatrix.hh"
#include "Tests.hh"
#include "Vector.hh"

using namespace scprog;

void test1 ()
{
  double data[4][2]{
    { 2.0, -1.0},
    {-1.0,  2.0},
    { 0.0, -1.0},
    { 0.0,  0.0}
  };

  CRSMatrix<double> A{4,2,5};

  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 2; ++j)
      if (data[i][j] != 0.0)
        A.set(i,j,data[i][j]);


  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 2; ++j)
      if (data[i][j] != 0.0)
        SCPROG_TEST(A.exists(i,j));

  A.compress();

  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 2; ++j)
      if (data[i][j] != 0.0)
        SCPROG_TEST(A.exists(i,j));

  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 2; ++j)
      SCPROG_TEST_EQ(A(i,j), data[i][j]);
}


void test2 ()
{
  CRSMatrix<double> A{3,3,3};

  A.set(2,2, 2.0);
  A.set(2,1, -1.0);
  A.set(1,2, -1.0);
  A.set(1,1, 2.0);
  A.set(1,0, -1.0);
  A.set(0,1, -1.0);
  A.set(0,0, 2.0);
  A.compress();

  Vector b(3);
  b[0] = 1.0;
  b[1] = 1.0;
  b[2] = 1.0;

  Vector y(3);
  A.mv(b, y);

  Vector x(3);
  x[0] = 1.0;
  x[1] = 0.0;
  x[2] = 1.0;

  for (std::size_t i = 0; i < 3; ++i)
    SCPROG_TEST_EQ(x[i], y[i]);
}


int main ()
{
  test1();
  test2();

  return report_errors();
}