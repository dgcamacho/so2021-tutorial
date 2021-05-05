/* This program calculates the largest eigenvalue of a given positive definit 
 * n x n matrix with real-valued entries as well as the correspondig eigen-
 * vector. It uses the power-method and approximates eigenvalues by calculating
 * the rayleigh-quotient.*/
 

#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>  // needed for std::sqrt; std::abs


using std::vector; using std::sqrt; using std::fabs;

double two_norm(vector<double> const &vec)
{   
    // Calculates euclidian norm of a given vector.
    double norm = 0;
    for (auto &i : vec) 
        norm += i*i;
    return sqrt(norm);
}

double inf_norm(vector<double> const &vec)
{
    // Calculates the infinity norm ||vec||_inf = max_i(|v_i|) of a given
    // vector.
    double norm = 0;
    for (auto &i : vec){
        norm = (norm > double(fabs(i)) ? norm : double(fabs(i)));
    }
    return norm;
}

double dot(vector<double> const &vec1, vector<double> const &vec2)
{
    // Returns the dot-product of two vectors of equal size.
    assert(vec1.size() == vec2.size());

    double scalar = 0;
    for (decltype(vec1.size()) i = 0; i < vec1.size(); ++i)
        scalar += vec1[i]*vec2[i];
    return scalar;
}

vector<double> mat_vec_mult(vector<double> const &vec, 
                            vector<vector <double>> const &A) 
{
    // Returns the product of an n x m matrix and a vector of dimension n, 
    // yielding a vector of dimension m.
    assert(vec.size() == A[0].size());

    vector<double> rhs_vec(vec.size());
    for (decltype(vec.size()) i = 0; i < vec.size(); ++i) {
        for (decltype(A[0].size()) j = 0; j < A[0].size(); ++j) {
            rhs_vec[i] += A[i][j]*vec[j];
        }
    }
    return rhs_vec;

}

void scale_vec(vector<double> &vec, double const &scale)
{
    // Scales each entry of a given vector by a certain real value.
    for (auto &i : vec) 
        i /= scale;
}

vector<double> vec_substract(vector<double> const &vec1, 
                             vector<double> const &vec2)
{
    // Given two vectors of equal size, this function returns the sub-
    // traction of the two vectors. 
    assert(vec1.size() == vec2.size());
    vector<double> vec_result(vec1.size());
    for (decltype(vec1.size()) i = 0; i < vec1.size(); ++i)
        vec_result[i] = vec1[i] - vec2[i]; 
    return vec_result;
}


vector<double> find_initial_value(vector<vector <double>> const &A, 
                          double const tol=1e-4) 
{
    // Given a n x m matrix, this function constructs a vector of dimension
    // n, that is linearly independent of the matrix. The entries of the vector
    // are filled with random variables that are uniformly distributed. 
    vector<double> vec(A[0].size());
    for (decltype(vec.size()) i = 0; i < vec.size(); ++i)
        vec[i] = std::rand()/((RAND_MAX + 1u)/5.0);
    auto rhs_vec = mat_vec_mult(vec, A);
    if (!(std::abs(two_norm(rhs_vec) - tol) >= 0))
        // ||A*vec||_2 = 0 iff A*vec = 0. This is not wanted -> new try
        vec = find_initial_value(A);
    return vec;
}


void print_vec(vector<double> const &vec) 
{
    // Simple function to write entries of vector to ostream
    for (auto &i : vec)
        std::cout << i << std::endl;
}

double rayleigh_quotient(vector<vector <double>> const &A, 
                        vector<double> const &vec)
{
    return dot(vec, mat_vec_mult(vec, A))/dot(vec , vec);
}


vector<double> approx_rvec(vector<double> const &vec, 
                 vector<vector <double>> const &A)
{
    // Approximates the eigenvalue of a given matrix A in the k-th 
    // iteration.
    vector<double> vec_tmp = mat_vec_mult(vec, A);
    scale_vec(vec_tmp, two_norm(vec_tmp));
    return vec_tmp;
}
double test(vector<vector <double>> const& A, 
                      vector<double> vec, double const sigma)
{   
    // Calculates the error of the implemented power method in the infinity
    // norm. 
    vector<double> vec_mult = mat_vec_mult(vec, A);
    scale_vec(vec, 1/sigma);
    double error = inf_norm(vec_substract(vec_mult, vec));
    return error;
}

void power_method(vector<vector <double>> const &A, 
                  unsigned const k=20)
{   
    // Iterates over a given number of iteration steps and calculates the 
    // largest eigenvalue and the corresponding eigenvector of a given 
    // positive-definit matrix A in each step. 
    vector<double> r_k = find_initial_value(A);
    double sigma = 0;
    for (int i = 1; i <= k; ++i){
        r_k = approx_rvec(r_k, A);
        sigma = rayleigh_quotient(A, r_k);
        std::cout << "The Rayleigh-Quotient in the step k=" << i << 
                     " is " << sigma << std::endl;
        std::cout << "The Error is " << test(A, r_k, sigma) << std::endl;
    }
}

int main()
{
    std::srand(0);

    vector<vector<double>> B{{3, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    power_method(B);
    vector<vector<double>> C{{4, -1, -1}, {0.5, 2, -1}, {0, 0, 1}};
    power_method(C);
    return 0;
}
