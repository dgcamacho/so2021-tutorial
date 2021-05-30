#include<iostream>
#include<vector>
#include<cassert>
#include<cmath>
#include<ctime>
#include<algorithm>    // std::all_of

using vec = std::vector<double>;
using mat = std::vector<vec>;

//fn for matrix vector product
vec mat_vec_prod(mat const& A, vec const& r){
	
	int m = A.size();       // rows in A
	int n = A[0].size();    // cols in A[1st vector]
	
	int p = r.size();				// rows in r
	
	//check the number of cols in matrix match with number of rows in vector
	assert(n == p);
	
	vec result(n, 0.0);
	
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; ++j){
			result[i] += A[i][j] * r[j];
        }
	}

	return result;	
}

double dot_prod(vec const& p, vec const& q){
	int m = p.size();       // rows in p
	int n = q.size();       // rows in q

	assert(m == n);

	double result = 0.0;

	for(int i = 0; i < m; i++){
		result += p[i] * q[i];
	}

	return result;
}

double rayleigh_quotient(mat const& A, vec const& r){
	vec Ar = mat_vec_prod(A, r);
	return dot_prod(r, Ar) / dot_prod(r,r);
}


bool vec_zero(vec const& r){
	int m = r.size();
	bool result = false;
	vec zero_vec(m, 0.0);

	if(r == zero_vec){
		result = true;
	}

	return result;
}

vec find_initial_value(mat const& A){
	int n = A[0].size();    // cols in A[1st vector]

	vec result(n, 0.0);

	std::srand(std::time(0)); //use current time as seed for random generator

	do {
		for(int i = 0; i < n; i++){
			result[i] = std::rand(); 
		}
	}
	while (vec_zero(mat_vec_prod(A, result)));

	return result;		
}

double two_norm(vec const& r){
	return std::sqrt(dot_prod(r,r));
}

vec scalar_vec_multi(vec const& r, double const& k){
	int m = r.size();
	vec result(m, 0.0);

	for(int i = 0; i < m; i++){ 
		result[i] = r[i] * k;
	}

	return result;
}

vec power_method(mat const& A, int const& k){
	
	vec r = find_initial_value(A);

	for(int i = 1; i <= k; i++){
		vec Ar = mat_vec_prod(A, r);
		double norm = two_norm(Ar);
		r = scalar_vec_multi(Ar, 1/norm);

		std::cout << "Rayleigh quotient for iteration " << i << " = " << rayleigh_quotient(A, r) << std::endl;
	}

	return r;
}

vec minus(vec const& p, vec const& q){
	int m = p.size();       // rows in p
	int n = q.size();       // rows in q

	assert(m == n);

	vec result(m, 0.0);

	for(int i = 0; i < m; i++){
		result[i] = p[i] - q[i];
	}

	return result;
}

void test(mat const& A, vec const& r, double const& sigma){
	vec Ar = mat_vec_prod(A, r);
	vec sigma_r = scalar_vec_multi(r, sigma);
	double l2_error = two_norm(minus(Ar, sigma_r));

	std::cout << "Two norm of the error = " << l2_error << std::endl;	
}


int main(){

	mat B = {{3.0,0.0,0.0},
             {0.0,1.0,0.0},
             {0.0,0.0,1.0}};

    mat C = {{4.0,-1.0,-1.0},
             {0.5,2.0,-1.0},
             {0.0,0.0,1.0}};

    int k = 20;

	std::cout << "For matrix B : " << std::endl;	
    vec eigenvector_B = power_method(B, k);
    double eigenvalue_B = rayleigh_quotient(B, eigenvector_B);
    test(B, eigenvector_B, eigenvalue_B);
    std::cout << std::endl;

	std::cout << "For matrix C : " << std::endl;	
    vec eigenvector_C = power_method(C, k);
    double eigenvalue_C = rayleigh_quotient(C, eigenvector_C);
    test(C, eigenvector_C, eigenvalue_C);
    std::cout << std::endl;

}