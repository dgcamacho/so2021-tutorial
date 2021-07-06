#include <iostream>

#include "CRSMatrix2.hh"
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

  CRSMatrix<double> A{4,2};

  {
    // create an inserter that fills the matrix `A` on destruction
    auto ins = A.inserter(5);

    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 2; ++j)
        if (data[i][j] != 0.0)
          ins(i,j) = data[i][j];
  }

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
  CRSMatrix<double> A{3,3};
  {
    auto ins = A.inserter(3);
    ins(2,2) =  2.0;  ins(2,1) = -1.0;
    ins(1,2) = -1.0;  ins(1,1) =  2.0;  ins(1,0) = -1.0;
                      ins(0,1) = -1.0;  ins(0,0) =  2.0;
  }

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