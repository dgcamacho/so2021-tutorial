#include <cmath>

#include "CGSolver.hh"
#include "Matrix.hh"
#include "Tests.hh"
#include "Vector.hh"

// test vector construction, size and element access
void test1 ()
{
  std::cout << "test 1..." << std::endl;
  // construct a vector with size 0
  Vector vec0{0};
  SCPROG_TEST_EQ(vec0.size(), 0);

  // construct a vector with size
  Vector vec1{10};
  SCPROG_TEST_EQ(vec1.size(), 10);

  // construct a vector with data
  std::vector<double> data(10, 0.0);
  Vector vec2{data};
  SCPROG_TEST_EQ(vec2.size(), 10);
  for (std::size_t i = 0; i < vec2.size(); ++i)
    SCPROG_TEST_EQ(vec2(i), 0.0);

  // construct a vector with brace-init-list
  Vector vec3({1.0,2.0,3.0,4.0,5.0});
  SCPROG_TEST_EQ(vec3.size(), 5);
  for (std::size_t i = 0; i < vec3.size(); ++i)
    SCPROG_TEST_EQ(vec3(i), double(i+1));

  // assign a constant to vector
  vec1 = 7.0;
  for (std::size_t i = 0; i < vec1.size(); ++i)
    SCPROG_TEST_EQ(vec1(i), 7.0);
}

// test vector-space operations
void test2 ()
{
  std::cout << "test 2..." << std::endl;
  Vector vec1({1.0,2.0,3.0,4.0,5.0}),
         vec2({2.0,3.0,4.0,5.0,6.0}),
         vec3({3.0,4.0,5.0,6.0,7.0});

  auto res1 = vec1.dot(vec2);
  SCPROG_TEST_EQ(res1, 70.0);

  auto res2 = vec1.two_norm();
  SCPROG_TEST_APPROX(res2, std::sqrt(1.0*1.0 + 2.0*2.0 + 3.0*3.0 + 4.0*4.0 + 5.0*5.0));

  // copmute the sum of two vectors
  Vector vec4 = vec1 + vec2;
  SCPROG_TEST_EQ(vec4.size(), vec1.size());

  // accumulated sum
  vec1 += vec2;
  for (std::size_t i = 0; i < vec1.size(); ++i) {
    SCPROG_TEST_EQ(vec1(i), vec4(i));
    SCPROG_TEST_EQ(vec1(i), (i+1.0) + (i+2.0));
  }

  Vector vec5 = vec4 - vec2;
  SCPROG_TEST_EQ(vec5.size(), vec4.size());

  // accumulated difference
  vec1 -= vec2;
  for (std::size_t i = 0; i < vec1.size(); ++i) {
    SCPROG_TEST_EQ(vec1(i), vec5(i));
    SCPROG_TEST_EQ(vec1(i), (i+1.0));
  }

  Vector vec6 = 2.0 * vec2;
  SCPROG_TEST_EQ(vec6.size(), vec2.size());
  for (std::size_t i = 0; i < vec2.size(); ++i)
    SCPROG_TEST_EQ(vec6(i), 2.0*vec2(i));
}

// test matrix construction, size and element access
void test3 ()
{
  std::cout << "test 3..." << std::endl;
  // construct a matrix with size 0
  Matrix mat0{0,0};
  SCPROG_TEST_EQ(mat0.rows(), 0);
  SCPROG_TEST_EQ(mat0.cols(), 0);

  // construct a matrix with size
  Matrix mat1{10,10};
  SCPROG_TEST_EQ(mat1.rows(), 10);
  SCPROG_TEST_EQ(mat1.cols(), 10);

  // construct a matrix with entries
  std::vector<std::vector<double>> entries{
    {1.0,2.0},
    {2.0,3.0}
  };
  Matrix mat2{entries};
  SCPROG_TEST_EQ(mat2.rows(), 2);
  SCPROG_TEST_EQ(mat2.cols(), 2);
  SCPROG_TEST_EQ(mat2(0,0), 1.0);
  SCPROG_TEST_EQ(mat2(0,1), 2.0);
  SCPROG_TEST_EQ(mat2(1,0), 2.0);
  SCPROG_TEST_EQ(mat2(1,1), 3.0);

  // construct a matrix with brace-init-list
  Matrix mat3({
    {1.0,2.0,3.0},
    {2.0,3.0,4.0}
  });
  SCPROG_TEST_EQ(mat3.rows(), 2);
  SCPROG_TEST_EQ(mat3.cols(), 3);
  SCPROG_TEST_EQ(mat3(0,0), 1.0);
  SCPROG_TEST_EQ(mat3(0,1), 2.0);
  SCPROG_TEST_EQ(mat3(0,2), 3.0);
  SCPROG_TEST_EQ(mat3(1,0), 2.0);
  SCPROG_TEST_EQ(mat3(1,1), 3.0);
  SCPROG_TEST_EQ(mat3(1,2), 4.0);

  mat1 = 7.0;
  for (std::size_t i = 0; i < mat1.rows(); ++i)
    for (std::size_t j = 0; j < mat1.cols(); ++j)
      SCPROG_TEST_EQ(mat1(i,j), 7.0);
}


// test matrix-vector operations
void test4 ()
{
  std::cout << "test 4..." << std::endl;
  Vector vec({2.0,3.0});
  Matrix mat({
    {1.0,2.0},
    {2.0,1.0}
  });

  Vector res(mat.rows());
  mat.mv(vec, res);
  SCPROG_TEST_EQ(res(0), 8.0);
  SCPROG_TEST_EQ(res(1), 7.0);

  Vector res2 = mat * vec;
  SCPROG_TEST_EQ(res.size(), res2.size());
  for (std::size_t i = 0; i < res2.size(); ++i)
    SCPROG_TEST_EQ(res(i), res2(i));
}

// Test the CG algorithm
void test5 ()
{
  std::cout << "test 5..." << std::endl;
  Vector b({1.0,1.0,1.0});
  Matrix A({
    { 2.0,-1.0, 0.0},
    {-1.0, 2.0,-1.0},
    { 0.0,-1.0, 2.0}
  });

  CGSolver solver{100, 1.e-10};
  Vector x = solver.solve(A,b);

  SCPROG_TEST_APPROX(x(0), 1.5);
  SCPROG_TEST_APPROX(x(1), 2.0);
  SCPROG_TEST_APPROX(x(2), 1.5);
}

int main ()
{
  test1();
  test2(); // 9 copy operations vs. 0 copy operations
  test3();
  test4();

  test5(); // 16+4 copy operations vs. 1+1 copy operations, 3 move operations (17 additional constructions)

  return scprog::report_errors();
}