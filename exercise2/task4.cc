/* This program calculates the largest eigenvalue of a given positive definit 
 * n x n matrix with real-valued entries as well as the correspondig eigen-
 * vector. It uses the power-method and approximates eigenvalues by calculating
 * the rayleigh-quotient.*/
 

#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>  // needed for std::sqrt; std::abs
#include <span>

using std::fabs;
using Vector = std::span<double>;

void printV(Vector const vec)
{
    for (int i = 0; i < vec.size(); ++i)
        std::cout << vec[i] << std::endl;
}

double &acces(double *Matrix, int const row, int const col, 
              int const nrows=3, int const ncols=3)
{
    return Matrix[row * nrows + col];
}

double* make_vector(int const size)
{
    return new double[size];
}

double* make_matrix(int const nrows, int const ncols)
{
    return new double[nrows * ncols];
}

double dot(Vector const vec1, Vector const vec2)
{
    assert(vec1.size() == vec2.size());
    double result = 0.0;
    for (int i = 0; i < vec1.size(); ++i)
        result += vec1[i]*vec2[i];
    return result;

}

double two_norm(double const value)
{
    return std::sqrt(value);
}

double inf_norm(Vector const vec)
{
    double norm = 0.0;
    for (int i = 0; i < vec.size(); ++i)
        norm = (norm > double(fabs(vec[i])) ? norm : double(fabs(vec[i])));
    return norm;
}

void mat_vec_mult(Vector const Matrix, Vector const vec, Vector result)
{
    assert(vec.size() == result.size());
    for (int i = 0; i < vec.size(); ++i){
        for (int j = 0; j < vec.size(); ++j)
            result[i] += Matrix[i*vec.size() + j]
                                *vec[j];
    }
}

void axpy(double const alpha, Vector const vec1, Vector vec2)
{
    assert(vec1.size() == vec2.size());
    for (int i = 0; i < vec1.size(); ++i)
        vec2[i] += alpha*vec1[i];
}
        
auto find_initial_value(Vector const A, int const ncols, int const nrows, 
                        int const tol = 1e-4)
{
    auto r0_data = make_vector(nrows);
    for (int i = 0; i < nrows; ++i){
        r0_data[i] = int(std::rand()/((RAND_MAX + 1u)/100.0));
    }
    auto r0 = Vector(r0_data, nrows);
    auto mult = Vector(make_vector(nrows), nrows);
    mat_vec_mult(A, r0, mult);
    assert((std::abs(two_norm(dot(mult, mult)) - tol) >= 0));
    return r0;
}

void scale(Vector vec, double const alpha)
{   
    for (int i = 0; i < vec.size(); ++i)
        vec[i] *= alpha;
}

void approx_rk(Vector const Matrix, Vector vec)
{
    mat_vec_mult(Matrix, vec, vec);
    double scaling = two_norm(dot(vec, vec));
    scale(vec, 1/scaling);
}

double rayleigh_quotient(Vector const Matrix, Vector const vec)
{
    auto mult = Vector(make_vector(vec.size()), vec.size());
    mat_vec_mult(Matrix, vec, mult);
    return dot(vec, mult)/dot(vec, vec);
}

double test(Vector const Matrix, Vector const vec, double const sigma)
{
    auto mult = Vector(make_vector(vec.size()), vec.size());
    mat_vec_mult(Matrix, vec, mult);
    scale(vec, sigma);
    axpy(-1.0, vec, mult);
    double error = inf_norm(mult);
    return error;
}

void power_method(Vector const A, int const nrows, int const ncols, 
                  int const k=20)
{
    auto rk = find_initial_value(A, nrows, ncols);
    double sigma = 0.0;
    for (int i = 0; i <= k; ++i){
        approx_rk(A, rk);
        double sigma = rayleigh_quotient(A, rk);
        std::cout << "The estimated Rayleigh-quotient in step k=" << i <<
                     " is " << sigma << std::endl;
        std::cout << "The error is " << test(A, rk, sigma) << std::endl;

        
    }
}

int main()
{
    std::srand(0);

    std::size_t const n = 3;
    std::size_t const m = 3;

    double mat[n*m] = {3, 0, 0, 0, 1, 0, 0, 0, 1};

    auto matrix = make_matrix(n, m);
    auto A = Vector(mat, n*m);


    power_method(A, n, m);

    return 0;
}
