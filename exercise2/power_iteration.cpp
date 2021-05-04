#include <iostream>
#include <cmath>
#include <ctime>

// calculate a matrix vector product
void product(int n, double* A, double r[], double p[] ) {
    for (int i = 0; i < n; i++) {
        p[i] = 0;
        for (int j = 0; j <n; j++) {
            p[i] += A[i*n+j] * r[j];
        }
    }
}

// calculate the dot product of two 1d vectors
double dot_product(int n, double u[], double v[]) {
    double dot_prod = 0.0;
    for (int i = 0; i < n; i++) {
        dot_prod += u[i] * v[i];
    }
    return dot_prod;
}

// calculate the rayleigh quotient
double rayleigh_quotient(int n, double* A, double r[]) {
    double p[n] = {};
    product(n, A ,r, p);
    return dot_product(n, r, p) / dot_product(n, r, r);
}

// test if a vector is not equal to the zero vector
bool not_trivial(int n, double r[]) {
    for (int i = 0; i< n; i++) {
        if (r[i] != 0) {
            return true;
        }
    }
    return false;
}

// for a given matrix find an initial vector such that the 
// matrix vector product is unequal to zero
void find_initial_value(int n, double* A, double r[]) {
    std::srand(std::time(0)); 
    while(true) {
        for (int i = 0; i < n; i++) {
            r[i] = std::rand();
        }
        double p[n] = {};
        product(n, A,r,p);
        if (not_trivial(n, p))
            break;
    }
}

double euclidean_norm(int n, double v[]) {
    double norm = 0;
    for (int i = 0; i < n; i++) {
        norm += v[i]*v[i];
    }
    return std::sqrt(norm);
}

void test(int n, double* A, double r[], double sigma) {
    double product_vec[n], result_vec[n];
    product(n, A, r, product_vec);
    for (int i = 0; i < n; i++)
        result_vec[i] = product_vec[i] - sigma * r[i];
    std::cout << "\nEuclidean norm: " << euclidean_norm(n, result_vec) << "\n";
}

void power_method(int n, double* A, int k) {
    double r[n], r1[n];
    double sigma;
    find_initial_value(n, A, r);
    for (int i = 0; i < k; i++) {
        product(n, A, r, r1);
        int norm = euclidean_norm(n, r1);
        for (int j = 0; j < n; j++) {
            r[j] = r1[j]/norm;
        }
        sigma = rayleigh_quotient(n, A, r);
        std::cout << "Rayleigh quotient = " << sigma << "\n";
    }
    test(n, A, r, sigma);
}



int main() {
    while(true) {
        int n = 0;
        int k = 0;
        std::cout << "\nPlease enter n (enter a value < 2 to exit).\n";
        std::cin >> n;
        if (n < 2)
            break;
        double* A = new double [n*n];
        double r[n] = {};
        double product[n] = {};
        double rk[n] = {};

        for (int i = 0; i < n; i++) {
            std::cout << "Please enter the next row of the matrix \n";
            for (int j = 0; j < n; j++) {
                std::cin >> A[i*n+j];
            } 
        }
        while (k<1) {
            std::cout << "\nPlease enter the number of iterations.\n";
            std::cin >> k;
        }
        power_method(n, A, k);

    }
}