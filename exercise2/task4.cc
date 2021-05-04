#include <iostream>
#include <cmath>
#include <cstdlib>


// global dimension for all calculations
int n = 0;

void print_vec(double * const v) {
    // print v nicely
    std::cout << "[";
    for (int i = 0; i < n - 1; ++i)
    {
        std::cout << v[i] << ", ";
    }
    std::cout << v[n - 1];
    std::cout << "]\n";
}

bool is_null_vec(double * const x) {
    // check if x is the zero vector
    double eps = std::numeric_limits<double>::epsilon();
    for(int i = 0; i < n; ++i) {
        if(std::abs(x[i]) >= eps){
            return false;
        }
    }
    return true;
}

double scalar_product(double * const x, double * const y) {
    // calculate the 2-scalar product of x, y
    double sp = 0;
    for (int i = 0; i < n; ++i) {
        sp += x[i] * y[i];
    }
    return sp;
}

void mat_dot_vec(double * const A, double * const x, double * res) {
    // calculate res := A * x
    
    // i:: row index in A
    for (int i = 0; i < n; ++i)
    {
        res[i] = 0;
        // j:: col index in A
        for (int j = 0; j < n; ++j)
        {
            res[i] += A[i * n + j] * x[j];
        }
    }
}

double norm(double * const x) {
    // calculate the 2-norm of x
    return std::sqrt(scalar_product(x, x));
}

double rayleigh_quotient(double * const A, double * const r) {
    // Calculate <r, Ar> / <r, r>
    double * prod = new double[n];
    mat_dot_vec(A, r, prod);
    double sp = scalar_product(r, prod);
    delete[] prod;
    return sp / scalar_product(r, r);
}

void find_initial_value(double * const A, double *r_0) {
    // Randomly select one Element NOT in ker A and write it to *r_0
    
    std::srand(11223344);
    double *tmp = new double[n];
    // get a randoom vector until it is not in ker A (tested experimentally)
    do {
        for (int i = 0; i < n; ++i)
        {
            double r = (double)std::rand() / RAND_MAX;
            r_0[i] = r;
        }
        mat_dot_vec(A, r_0, tmp);
    } while (is_null_vec(tmp));
    delete[] tmp;
}

void power_method(double * const A, int const k) {
    // calculate r_k by iteration. print sigma(A, r_i) for each step

    double *r = new double[n];
    double *tmp = new double[n];
    find_initial_value(A, r);
    std::cout << "Using Initial Value ";
    print_vec(r);
    for (int i = 0; i < k; ++i)
    {
        std::cout << "Iteration Step " << i + 1 << '\n';
        // r := A r / norm(Ar)
        mat_dot_vec(A, r, tmp);
        double tmp_norm = norm(tmp);
        for (int j = 0; j < n; ++j)
        {
            r[j] = tmp[j] / tmp_norm;
        }
        std::cout << "New Rayleigh-Quotient = " << rayleigh_quotient(A, r) << '\n';
    }
    delete[] r;
    delete[] tmp;
}

double test(double * const A, double * const r, double const sigma) {
    // Return ||Ar - sigma r||
    double * tmp = new double[n];
    mat_dot_vec(A, r, tmp);
    for (int i = 0; i < n; ++i)
    {
        tmp[i] -= sigma * r[i];
    }
    double res = norm(tmp);
    delete[] tmp;
    return res;
}

int main() {
    std::cout << "A\n";
    n = 3;
    double *A = new double[n * n];
    A[0] = 3;
    A[3 * 1 + 1] = 1;
    A[3 * 2 + 2] = 1;
    power_method(A, 20);
    delete[] A;

    std::cout << "B\n";
    n = 3;
    double *B = new double[n * n];
    B[0] = 4;
    B[1] = B[2] = B[1 * n + 2] = -1;
    B[1 * n + 1] = 2;
    B[1 * n + 0] = 0.5;
    power_method(B, 20);
    delete[] B;
    return 0;
}