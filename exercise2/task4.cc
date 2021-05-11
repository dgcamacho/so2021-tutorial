#include <cmath>
#include <iostream>
#include <cstdlib>
#include <array>
#include <numeric>
#include <random>
#include <ctime>
#include <algorithm>
#include <iomanip>

const int n = 3;
typedef long double Rational;

typedef std::array< Rational, n > Vector;
typedef std::array< Vector, n > Matrix;

Rational rayleight_quotient( Matrix const& A, Vector const& r ) {
    Rational    dotProduct,
                aRProduct;
    Vector aR;

    dotProduct = std::inner_product(r.begin(), r.end(), r.begin(), Rational{0});
    
    for( std::size_t i = 0; i < r.size(); i++ ) {
        aR[i] = std::inner_product(r.begin(), r.end(), A[i].begin(), Rational{0});
    }
    aRProduct = std::inner_product( aR.begin(), aR.end(), r.begin(), Rational{0});

    return aRProduct / dotProduct;
}

Vector find_initial_value(Matrix const& A) {
    Vector test;
    std::srand(std::time(nullptr));

    bool flag = false;
    do{
        // ensure the initial test vector has components \in (0,1) to be within the range of best arithmetic precision
        for( auto i = 0; i < test.size(); i++ ) {
            test[i] = static_cast<Rational>(std::rand()) / RAND_MAX;
        }

        //check if at least one component A*r is nonzero, i.e. r \notin \ker A
        for( auto i = A.begin(); i != A.end(); i++ ) {
            if( std::inner_product(i->begin(), i->end(), test.begin(), Rational{0}) > 1e-14 ) {
                flag = true;
                break;
            }
        }
    }
    while( !flag  );

    return test;
}

Vector power_method(Matrix const& A, std::size_t const& k) {
    Vector r = find_initial_value(A);

    for( std::size_t i = 0; i < k; i++ ) {
        Rational dotProduct{0};
        Vector newR;
        for( std::size_t j = 0; j < r.size(); j++ ) {
            newR[j] = std::inner_product(r.begin(), r.end(), A[j].begin(), Rational{0});
            dotProduct += newR[j]*newR[j];
        }
        
        for( std::size_t j = 0; j < r.size(); j++ ) {
            r[j] = newR[j] / dotProduct;
        }
        std::cout << std::setw(std::ceil(std::log10(k))) <<  i << ": " << rayleight_quotient( A, r ) << std::endl;
    }

    return r;
}

void test(Matrix const& A, Vector const& r, Rational sigma) {
    Vector aR;
    for( std::size_t i = 0; i < r.size(); i++) {
        aR[i] = std::inner_product( A[i].begin(), A[i].end(), r.begin(), Rational{0} ) - sigma * r[i];
    }

    Rational const error = std::inner_product( aR.begin(), aR.end(), aR.begin(), Rational{0} );

    std::cout << "Error (2-Norm): " << error << std::endl;
}

int main(int argc, char** argv) {
    std::array<Matrix,2> matrices;
    matrices[0] = Matrix {3, 0, 0,
                         0, 1, 0,
                         0, 0, 1};

    matrices[1] = Matrix{  4, -1, -1,
                         0.5,  2, -1,
                           0,  0,  1};

    for( auto const& matrix : matrices ) {
        std::cout << "New Matrix" << std::endl;
        Vector const r = power_method( matrix, 20 );
        test(matrix, r, rayleight_quotient(matrix, r) );
    }

    return EXIT_SUCCESS;
}
