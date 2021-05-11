#include <cassert>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using std::vector;

double dot(vector<double> const &vec1, vector<double> const &vec2){
    assert(vec1.size() == vec2.size());
    double scalar = 0;
    for (decltype(vec1.size()) i = 0; i < vec1.size(); i++){
        scalar += vec1[i] * vec2[i];
    }
    return scalar;
}

auto two_norm(vector<double> const &vec) -> double
    {
        return std::sqrt(dot(vec, vec));
    }

auto inf_norm(vector<double> const &vec) -> double{
    double norm = 0;
    for(auto &i : vec){
        norm = (norm > double(fabs(i)) ? norm : double(fabs(i)));
    }
    return norm;
}

auto inf_norm_stackoverflow(vector<double> const &vec) -> double{
    // Return the inf norm to test conversion
    return *max_element(std::begin(vec), std::end(vec));
}

auto find_initial_value(vector<vector<double>> &A) -> vector<double>{
    vector<double> r(A.size());
    for(decltype(r.size()) i = 0; i < r.size(); ++i){
        //std::cout << (RAND_MAX);
        r[i] = std::rand()/((RAND_MAX + 1u)/10);
    }
    return r;
}

vector<double> mat_vec_mult(vector<vector<double>> const &A, vector<double> const &r){
    assert(r.size() == A[0].size());
    vector<double> result(r.size());
    for(decltype(r.size()) i = 0; i < r.size(); ++i){
        for(decltype(A[0].size()) j = 0; j < A[0].size(); ++j){
            result[i] += A[i][j]*r[j];}
    }
return result;
}

auto elementwise_division(vector<double> const &vec, double divisor) -> vector<double>{
    assert(divisor!=0);
    vector<double> result(vec.size());
    for(int i = 0; i < vec.size(); ++i){
        result[i] = vec[i] / divisor;
    }
    return result;
}

auto elementwise_multiplication(vector<double> const &vec, double multiplicator) -> vector<double>{
    vector<double> result(vec.size());
    for(int i = 0; i < vec.size(); ++i){
        result[i] = vec[i] * multiplicator;
    }
    return result;
}

auto elementwise_difference(vector<double> const &vec1, vector<double> const &vec2) -> vector<double>{
    assert(vec1.size() == vec2.size());
    vector<double> result(vec1.size());
    for(int i = 0; i < vec1.size(); ++i){
        result[i] = vec1[i] - vec2[i];
    }
    return result;
}

auto rayleigh_quotient(vector<vector<double>> const &A, vector<double> const &r) -> double {
return dot(r, mat_vec_mult(A, r))/dot(r, r);
}

auto approximate_r_vector(vector<vector<double>> const &A, vector<double> &r) -> vector<double>{
    vector<double> product_a_r = mat_vec_mult(A, r);
    double norm_a_r = two_norm(product_a_r);
    return elementwise_division(product_a_r, norm_a_r);
}

auto test(vector<vector<double>> &A, vector<double> &r, double &sigma) -> double {
    auto a_r = mat_vec_mult(A, r);
    auto r_sigma = elementwise_multiplication(r, sigma);
    auto difference = elementwise_difference(a_r, r_sigma);
    return inf_norm_stackoverflow(difference);
}

auto power_method(vector<vector<double>> &A, int const k = 10) -> void{
    vector<double> r = find_initial_value(A);
    for(int i = 0; i < k; ++i){
        r = approximate_r_vector(A, r);
        double sigma = rayleigh_quotient(A, r);
        std::cout << "Iteration " << i << std::endl;
        std::cout << "Largest Eigenvalue " << sigma << std::endl;
        std::cout << "Error norm " << test(A, r, sigma) << std::endl << std::endl;
    }
}

int main() {
    int const k = 20;
    vector<vector<double>> B{{3, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    power_method(B, k);
    vector<vector<double>> C{{4, -1, -1}, {0.5, 2, -1}, {0, 0, 1}};
    power_method(C, k);
}