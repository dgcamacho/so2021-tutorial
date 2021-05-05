/* This program calculates the largest eigenvalue of a given positive definit 
 * n x n matrix with real-valued entries as well as the correspondig eigen-
 * vector. It uses the power-method and approximates eigenvalues by calculating
 * the rayleigh-quotient.*/
 

#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>  // needed for std::sqrt; std::abs
#include <span>

using std::fabs; using std::sqrt; //using typical mathematical functions 
using Vector = std::span<double>; //alias for a Vector-type 

// prints the entries of a given vector
void printV(Vector const vec)
{
    for (int i = 0; i < vec.size(); ++i)
        std::cout << vec[i] << std::endl;
}

// copies entries of one vector into another without copying memory adress
void cpV(Vector const vec1, Vector vec2)
{
    assert(vec1.size() == vec2.size());
    for (int i = 0; i < vec1.size(); ++i)
        vec2[i] = vec1[i];
}

// accessing the entries of a matrix by giving the row- and col-position
// and mapping it to the implemented matrix in 1D-form
double &acces(double *Matrix, int const row, int const col, 
              int const nrows=3, int const ncols=3)
{
    return Matrix[row * nrows + col];
}

// initialising a vector
double* make_vector(int const size)
{
    return new double[size];
}

// initialising a matrix
double* make_matrix(int const nrows, int const ncols)
{
    return new double[nrows * ncols];
}

// calculates the dot-product of two given vectors of above defined Vector-
// type
double dot(Vector const vec1, Vector const vec2)
{
    assert(vec1.size() == vec2.size());
    double result = 0.0;
    for (int i = 0; i < vec1.size(); ++i)
        result += vec1[i]*vec2[i];
    return result;

}

// calculates the euclidian norm (||vec||_2)^2 = sum_i(vec_i^2)
double two_norm(double const value)
{
    return sqrt(value);
}

//calculates the infinity norm ||vec||_inf = max |vec_i|
double inf_norm(Vector const vec)
{
    double norm = 0.0;
    for (int i = 0; i < vec.size(); ++i)
        norm = (norm > double(fabs(vec[i])) ? norm : double(fabs(vec[i])));
    return norm;
}

//calculates the product of a matrix and a given vector
void mat_vec_mult(Vector const Matrix, Vector vec, Vector result)
{
    assert(vec.size() == result.size());
    for (int i = 0; i < vec.size(); ++i){
        double f = 0.0;
        for (int j = 0; j < vec.size(); ++j)
            f += Matrix[i*vec.size() + j]
                                *vec[j];
        result[i] = f;
    }
}

//calculates y=a*x + y
void axpy(double const alpha, Vector const vec1, Vector vec2)
{
    assert(vec1.size() == vec2.size());
    for (int i = 0; i < vec1.size(); ++i)
        vec2[i] += alpha*vec1[i];
}
//finds the initial approximation of a potential eigenvector. This initial
//approximation should be linearly independent, thus A*r0 != 0.
auto find_initial_value(Vector const A, int const ncols, int const nrows, 
                        int const tol = 1e-12)
{
    auto r0_data = make_vector(nrows);
    for (int i = 0; i < nrows; ++i){
        r0_data[i] = int(std::rand()/((RAND_MAX + 1u)/10.0));
    }
    auto r0 = Vector(r0_data, nrows);
    auto mult = Vector(make_vector(nrows), nrows);
    mat_vec_mult(A, r0, mult);
    // ||A*r0||_2 == 0 iff A*r0 == 0. Thus, assertion if norm greater zero
    assert((std::abs(two_norm(dot(mult, mult))) - tol) > 0);
    return r0;
}

// scales every vector entry by a real number
void scale(Vector vec, double const alpha)
{   
    for (int i = 0; i < vec.size(); ++i)
        vec[i] *= alpha;
}

// calculates approximation of a potential eigenvector in the k-th iteration
void approx_rk(Vector const Matrix, Vector vec)
{  
    auto v_scale = Vector(make_vector(vec.size()), vec.size());
    mat_vec_mult(Matrix, vec, v_scale);
    double scaling = two_norm(dot(v_scale, v_scale));
    scale(v_scale, 1/scaling);
    cpV(v_scale, vec);
}

// calculates the rayleigh-quotient of a given matrix and a given vector
double rayleigh_quotient(Vector const Matrix, Vector const vec)
{
    auto mult = Vector(make_vector(vec.size()), vec.size());
    mat_vec_mult(Matrix, vec, mult);
    return dot(vec, mult)/dot(vec, vec);
}

// calculates the error of the approximation in the infinity_norm to compare
// entry-wise the accurateness of the solution
double test(Vector const Matrix, Vector const vec, double const sigma)
{
    auto mult = Vector(make_vector(vec.size()), vec.size());
    auto scaled = Vector(make_vector(vec.size()), vec.size());
    cpV(vec, scaled);
    mat_vec_mult(Matrix, vec, mult);
    scale(scaled, sigma);
    axpy(-1.0, scaled, mult);
    double error = inf_norm(mult);
    return error;
}

// routine of the power-method. The largest eigenvalue and the corresponding
// eigenvector are estimated in k iterations and the error is evaluated.
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

    double mat1[n*m] = {3, 0, 0, 0, 1, 0, 0, 0, 1};
    double mat2[n*m] = {4, -1, -1, 0.5, 2, -1, 0, 0, 1};

    auto B = Vector(mat1, n*m);
    auto C = Vector(mat2, n*m);

    power_method(B, n, m);
    power_method(C, n, m);
    return 0;
}
