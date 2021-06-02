#include <algorithm>    // std::max
#include <cmath>        // std::abs, std::sqrt
#include <ctime>        // std::time
#include <iostream>     // std::cout, std::endl

/// Dot product `<r,s> = r^T * s`
double dot (double const r[3], double const s[3])
{
  return r[0]*s[0] + r[1]*s[1] + r[2]*s[2];
}

/// Matrix-vector product `y = A * x`
void matvec (double const A[3][3], double const x[3], double y[3])
{
  for (int i = 0; i < 3; ++i) {
    y[i] = 0.0;

    for (int j = 0; j < 3; ++j)
      y[i] += A[i][j] * x[j];
  }
}

/// Return the maximum of the absolute values of the vector
double abs_max (double const r[3])
{
  return std::max({std::abs(r[0]), std::abs(r[1]), std::abs(r[2])});
}

/// Return the Rayleigh quotient
/**
 * \param A  System matrix
 * \param r  Eigenvector approximation
 *
 * \return Rayleigh quotient `<r,Ar>/<r,r>`
 **/
double rayleigh_quotient (double const A[3][3], double const r[3])
{
  double s[3];
  matvec(A,r,s);
  return dot(r,s)/dot(r,r);
}

/// Compute a random initial vector that is not in the kernel of A
/**
 * \param A      System matrix
 * \param[out] r Initial eigenvector approximation with `Ar != 0`
 **/
void find_initial_value (double const A[3][3], double r[3])
{
  double s[3];
  do {
    // random integral values in the interval [-10, 10]
    r[0] = std::rand() % 20 - 10;
    r[1] = std::rand() % 20 - 10;
    r[2] = std::rand() % 20 - 10;

    // check whether vector is in ther kernel of the matrix
    matvec(A,r,s);
  }
  while (abs_max(s) < 1.e-12);
}

/// Compute the error of the eigenvector approximation and print to cout
/**
 * \param A      System matrix
 * \param r      Eigenvector approximation
 * \param sigma  Eigenvalue approximation
 *
 * Comput the error norm `|Ar - sigma*r|`
 **/
void test (double const A[3][3], double const r[3], double const sigma)
{
  double s[3];
  matvec(A, r, s);

  s[0] -= sigma * r[0];
  s[1] -= sigma * r[1];
  s[2] -= sigma * r[2];

  std::cout << "r = [" << r[0] << ", " << r[1] << ", " << r[2] << "], "
               "sigma = " << sigma << ", "
               "err = " << std::sqrt(dot(s,s)) << std::endl;
}

/// Power iteration: `r^(k) = Ar^(k-1)/|Ar^(k-1)|`
/**
 * \param A  Matrix to compute the eigenvector and eigenvalue of
 * \param k  Number of power iterations
 **/
void power_method (double const A[3][3], int const k)
{
  double r[3];
  find_initial_value(A, r);

  double s[3];
  for (int i = 1; i <= k; ++i) {
    matvec(A, r, s);
    double const nrm = std::sqrt(dot(s,s));

    r[0] = s[0]/nrm;
    r[1] = s[1]/nrm;
    r[2] = s[2]/nrm;

    double const sigma = rayleigh_quotient(A,r);

    std::cout << i << ") ";
    test(A, r, sigma);
  }
}

int main ()
{
  // initial random seed
  std::srand(std::time(nullptr));

  std::cout << "Matrix B:" << std::endl;
  double B[3][3] = {
    {3.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {0.0, 0.0, 1.0}
  };
  power_method(B, 20);

  std::cout << std::endl;
  std::cout << "Matrix C:" << std::endl;
  double C[3][3] = {
    {4.0, -1.0, -1.0},
    {0.5,  2.0, -1.0},
    {0.0,  0.0,  1.0}
  };
  power_method(C, 20);
}