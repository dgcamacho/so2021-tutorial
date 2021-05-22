#include <iostream>
#include "LU.hh"
#include "DenseMatrix.hh"
#include "Vector.hh"

namespace scprog
{
    void LU::compute(DenseMatrix const& m) {
        // n dimension of square matrix m
        const DenseMatrix::size_type n = m.cols();  

        // initialize decomposition matrix
        decomposition_ = DenseMatrix(n,n);

        // sum stores sum of products of matrix entries
        double sum = 0;

        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                sum = 0;
                for (int k = 0; k < i; ++k) {
                    sum += decomposition_(i,k) * decomposition_(k,j);
                }
                decomposition_(i,j) = m(i,j) - sum;
            }
            for (int j = i + 1; j < n; ++j) {
                sum = 0;
                for (int k = 0; k < i; ++k) {
                    sum += decomposition_(j,k) * decomposition_(k,i);
                }
                decomposition_(j,i) = (1 / decomposition_(i,i)) * (m(j,i) - sum);
            }
        }
    }

    void LU::apply (Vector const& b, Vector& x) const
    {
        // A = LU, Ax = b --> b = LUx
        // 1. solve Ly = b for y

        // n dimension of square matrix m
        const int n = decomposition_.cols();  
        double sum;
        Vector y = Vector(n);

        for (int i = 0; i < n; ++i) {
            sum = 0;
            for (int k = 0; k < i; ++k)
                sum += decomposition_(i,k) * y[k];
            y[i] = b[i] - sum;
        }

        // 2. solve Ux = y for x
        for (int i = n - 1; i >= 0; --i) {
            sum = 0;
            for (int k = i + 1; k < n; ++k)
                sum += decomposition_(i,k) * x[k];
            x[i] = (1 / decomposition_(i,i)) * (y[i] - sum);
        }
    }
}