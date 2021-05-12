#include<iostream>
#include<vector>
#include<cassert>
#include <cmath>

using vector_d = std::vector<double>;
using matrix_d = std::vector<std::vector<double>>;

///////////////////////////////////////////////////////////////////
// vector operations

// print a vector
// input:   vector of arbitrary dimension 
// returns: nothing
void print_vector(vector_d x){
    int n = x.size();
    std::cout << "\n" << "[ ";
    for(int i = 0; i < n-1; ++i){
        std::cout << x[i] << ", ";
    }
    std::cout << x[n-1] << " ]" << std::endl;
}

// check if vector is (almost) zero
// input:   vector of arbitrary dimension 
// returns: true iff all components are below a presicion value eps
bool vec_is_zero(vector_d x){
    int eps = 1e-5; 
    for(int i = 0; i < x.size(); ++i){
        if(! (x[i] < eps)) 
            return false;
    }
    return true;
}

// difference of vectors: x - y
// input:   two n-vectors 
// returns: n-vector
vector_d diff(vector_d x, vector_d y){
    assert(x.size() == y.size());
    vector_d result(x.size(), 0.0);

    for(int i = 0; i < x.size(); ++i){
        result[i] = x[i] - y[i];
    }

    return result;
}

// scalar multiplication of vectors: c*x
// input:   scalar c and n-vector x 
// returns: n-vector
vector_d scal_vec_prod(double c, vector_d x){
    vector_d result(x.size(), 0.0);
    for(int i = 0; i < x.size(); ++i){
        result[i] = c * x[i];
    }
    return result;
}

// euclidean dot product: x^T*y
// input:   two vectors of same dimension 
// returns: euclidean dot product (double)
double dot_product(vector_d const x, vector_d const y){
    assert(x.size() == y.size());
    int n = x.size();
    double result = 0.;
    for(int i = 0; i < n; ++i){
        result += x[i] * y[i];
    }
    return result;
}

// euclidean norm: || x ||
// input:   vector of arbitrary dimension 
// returns: euclidean norm (double)
double norm(vector_d x){
    return std::sqrt(dot_product(x,x));
}


///////////////////////////////////////////////////////////////////
// matrix - vector operations

// matrix vector product: A*x
// input:   A is a mxn-matrix, x is a m-vector 
// returns: n-vector
vector_d mat_vec_product(matrix_d A, vector_d x){
    int n = A.size();       // number of rows in A
    int m = A[0].size();    // number of cols in A

    assert(m == x.size());

    vector_d result(n,0.0); // initalize a result vector of suitable dimension
    
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            result[i] += A[i][j] * x[j];
        }
    }
    
    return result;
}


///////////////////////////////////////////////////////////////////
// eigenvector & eigenvalue

double rayleigh_quotient(matrix_d A, vector_d r){
    vector_d Ar = mat_vec_product(A,r);
    double num = dot_product(r,Ar);
    double denom = norm(r);
    
    return num / denom;
}

vector_d find_initial_value(matrix_d A){
    int n = A[0].size();
    vector_d r0(n, 0.0);
    
    std::srand(1);  

    // generate random components of r0 and check wether the resulting r0 lies in the kernel of A
    do{
        for(int i = 0; i < n; ++i){
            r0[i] = std::rand(); 
        }
    } while (vec_is_zero(mat_vec_product(A, r0)));

    return r0;
}

vector_d power_method(matrix_d A, int k){
    vector_d r = find_initial_value(A);
    double sigma = 0;
    
    for(int i = 1; i <= k; ++i){
        r = scal_vec_prod(1 / norm(mat_vec_product(A,r)), mat_vec_product(A,r));
        sigma = rayleigh_quotient(A,r);
        
        std::cout << "rayleigh quotient of iteration " << i << ": " << sigma << std::endl;
    }

    return r;
}

double test(matrix_d A, vector_d r, double sigma){
    vector_d Ar = mat_vec_product(A,r);
    vector_d sigmar = scal_vec_prod(sigma,r);
    
    double err = norm(diff(Ar, sigmar));
    
    std::cout << "approximation error: " << err << std::endl;
    
    return err;
}

///////////////////////////////////////////////////////////////////

int main(){

    matrix_d B = {{3.,0.,0.},
                  {0.,1.,0.},
                  {0.,0.,1.}};
    matrix_d C = {{4. ,-1.,-1.},
                  {0.5, 2.,-1.},
                  {0. , 0., 1.}};

    int k = 20;

    std::cout << "matrix B:" << std::endl;
    vector_d eigenvector_B = power_method(B, k);
    double eigenvalue_B    = rayleigh_quotient(B, eigenvector_B);
    test(B, eigenvector_B, eigenvalue_B);
    std::cout << "\n";

    std::cout << "matrix C:" << std::endl;
    vector_d eigenvector_C = power_method(C, k);
    double eigenvalue_C    = rayleigh_quotient(C, eigenvector_C);
    test(C, eigenvector_C, eigenvalue_C);
    std::cout << "\n";

}