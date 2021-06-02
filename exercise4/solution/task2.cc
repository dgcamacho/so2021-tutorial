#include <cmath>
#include <iostream>
#include <limits>

#include "DenseMatrix.hh"
#include "Vector.hh"
#include "Timer.hh"

using namespace scprog;

template <class T>
bool almost_equal (T x, T y, int ulp = 2)
{
  return std::abs(x-y) <= std::numeric_limits<T>::epsilon() * std::abs(x+y) * ulp
      || std::abs(x-y) < std::numeric_limits<T>::min();
}


template <class Mat, class Vec>
bool benchmark (std::size_t n = 100, int repeat = 100)
{
  // a timer is used for simple benchmarking
  Timer t;

  double measurement[4] = {};
  bool all_pass = true;
  for (int iter = 0; iter < repeat; ++iter)
  {
    // 1. create the matrix and the vector
    t.reset();
    Mat mat(n, n);
    Vec vec(n), result(n);
    measurement[0] += t.elapsed();

    // 2. fill the matrix
    t.reset();
    mat(0,0) = 2.0;
    for (std::size_t i = 1; i < n; ++i) {
      mat(i,i) = 2.0;
      mat(i-1,i) = -1.0;
      mat(i,i-1) = -1.0;
    }
    measurement[1] += t.elapsed();

    // 3. fill the vector
    t.reset();
    for (std::size_t i = 0; i < n; ++i) {
      vec[i] = 1.0;
    }
    measurement[2] += t.elapsed();

    // 4. perform a matrix-vector product operation
    t.reset();
    mat.mv(vec, result);
    measurement[3] += t.elapsed();

    // 5. compare the result
    bool pass = almost_equal(result[0], 1.0) && almost_equal(result[n-1], 1.0);
    for (std::size_t i = 1; i < n-1; ++i) {
      pass = pass && almost_equal(result[i], 0.0);
    }
    all_pass = all_pass && pass;
  }

  // Print measurement results
  std::cout << "Measurements for type " << typeid(Mat).name() << ":\n"
               "  initialization:  " << (measurement[0]*1000.0/repeat) << " ms\n"
               "  fill the matrix: " << (measurement[1]*1000.0/repeat) << " ms\n"
               "  fill the vector: " << (measurement[2]*1000.0/repeat) << " ms\n"
               "  mat-vec product: " << (measurement[3]*1000.0/repeat) << " ms\n"
               "  pass: " << all_pass << "\n" << std::endl;

  return all_pass;
}

int main()
{
  bool pass = benchmark<DenseMatrix, Vector>(2000, 100);

  return pass ? 0 : 42;
}

// compile with:
// c++ -O2 DenseMatrix.cc Vector.cc task2.cc -o task2