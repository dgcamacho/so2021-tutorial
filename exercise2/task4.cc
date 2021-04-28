#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>

using std::vector;

double two_norm(vector<double> const &vec)
{   
    double norm = 0;
    for (auto &i : vec) 
        norm += i*i;
    return std::sqrt(norm);
}

vector<double> mat_vec_mult(vector<double> const &r, 
                            vector<vector <double>> const &A) 
{
    assert(r.size() == A[0].size());

    vector<double> rhs_vec(r.size());
    for (decltype(r.size()) i = 0; i < r.size(); i++) {
        for (decltype(A[0].size()) j = 0; j < A[0].size(); j++) {
            rhs_vec[i] += A[i][j]*r[j];
        }
    }
    return rhs_vec;

}
void fill_rvec_0(vector<double> &r, 
                 vector<vector <double>> const &A, double const tol=1e-4) 
{
    for (decltype(r.size()) i = 0; i < r.size(); i++)
        r[i] = std::rand()/((RAND_MAX + 1u)/6);
    auto rhs_vec = mat_vec_mult(r, A);
    if (!(std::abs(two_norm(rhs_vec) - tol) >= 0))
        fill_rvec_0(r, A);
}


void print_vec(vector<double> vec) {
    for (auto &i : vec)
        std::cout << i << std::endl;
}

int main()
{
    std::srand(0);
    std::size_t n = 3;

    vector<vector<double>> A{{3, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    vector<double> r(n);
    fill_rvec_0(r, A);
    print_vec(r);
    auto rhs_vec = mat_vec_mult(r, A);
    std::cout << (two_norm(rhs_vec)) << std::endl;



}
