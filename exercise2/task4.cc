#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <algorithm>

using std::vector;

double two_norm(vector<double> const &vec)
{   
    double norm = 0;
    for (auto &i : vec) 
        norm += i*i;
    return std::sqrt(norm);
}

double inf_norm(vector<double> const &vec)
{
    double norm = 0;
    for (auto &i : vec)
        norm = std::max(norm, double(abs(i)));
    return norm;
}

double dot(vector<double> const &vec1, vector<double> const &vec2)
{
    assert(vec1.size() == vec2.size());

    double scalar = 0;
    for (decltype(vec1.size()) i = 0; i < vec1.size(); ++i)
        scalar += vec1[i]*vec2[i];
    return scalar;
}

vector<double> mat_vec_mult(vector<double> const &r, 
                            vector<vector <double>> const &A) 
{
    assert(r.size() == A[0].size());

    vector<double> rhs_vec(r.size());
    for (decltype(r.size()) i = 0; i < r.size(); ++i) {
        for (decltype(A[0].size()) j = 0; j < A[0].size(); ++j) {
            rhs_vec[i] += A[i][j]*r[j];
        }
    }
    return rhs_vec;

}

void scale_vec(vector<double> &vec, double const &scale)
{
    for (auto &i : vec) 
        i /= scale;
}

vector<double> vec_substract(vector<double> const &vec1, 
                             vector<double> const &vec2)
{
    assert(vec1.size() == vec2.size());
    vector<double> vec_result(vec1.size());
    for (decltype(vec1.size()) i = 0; i < vec1.size(); ++i)
        vec_result[i] = vec1[i] - vec2[i]; 
    return vec_result;
}


vector<double> fill_vec_0(vector<vector <double>> const &A, 
                          double const tol=1e-4) 
{
    vector<double> vec(A[0].size());
    for (decltype(vec.size()) i = 0; i < vec.size(); ++i)
        vec[i] = std::rand()/((RAND_MAX + 1u)/6);
    auto rhs_vec = mat_vec_mult(vec, A);
    if (!(std::abs(two_norm(rhs_vec) - tol) >= 0))
        vec = fill_vec_0(A);
    return vec;
}


void print_vec(vector<double> const &vec) 
{
    for (auto &i : vec)
        std::cout << i << std::endl;
}

double rayleigh_quotient(vector<vector <double>> const &A, 
                        vector<double> const &vec)
{
    return dot(vec, mat_vec_mult(vec, A))/dot(vec , vec);
}


vector<double> approx_rvec(vector<double> &vec, 
                 vector<vector <double>> const &A)
{
    vector<double> vec_tmp = mat_vec_mult(vec, A);
    scale_vec(vec_tmp, two_norm(vec_tmp));
    return vec_tmp;
}
double error_two_norm(vector<vector <double>> const& A, 
                      vector<double> vec, double const sigma)
{   
    vector<double> vec_mult = mat_vec_mult(vec, A);
    scale_vec(vec, 1/sigma);
    double error = inf_norm(vec_substract(vec_mult, vec));
    return error;
}

double power_method(vector<vector <double>> const &A, 
                    vector<double> &vec, unsigned const k=20)
{   
    vector<double> r_k = vec;
    double sigma = 0;
    for (int i = 1; i <= k; ++i){
        r_k = approx_rvec(r_k, A);
        sigma = rayleigh_quotient(A, r_k);
        std::cout << "The Rayleigh-Quotient in the step k=" << i << 
                     " is " << sigma << std::endl;
        std::cout << "The Error is " << error_two_norm(A, r_k, sigma) << std::endl;
    }
    return 0;
}

int main()
{
    std::srand(0);
    std::size_t n = 3;

    vector<vector<double>> A{{4, -1, -1}, {0.5, 2, -1}, {0, 0, 1}};
    auto r = fill_vec_0(A);
    print_vec(r);
    auto r_k = approx_rvec(r, A);
    print_vec(r_k);
    double sigma = power_method(A, r);
}
