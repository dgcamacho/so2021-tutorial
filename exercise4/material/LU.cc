#include <iomanip>

#include "DenseMatrix.hh"
#include "LU.hh"
#include "Vector.hh"

namespace scprog
{
    LU::LU (DenseMatrix::size_type const n) : decomposition_(n,n) {}

    // decomposing the matrix m, without modifing it
    void LU::compute (DenseMatrix const& mat) {
        const DenseMatrix::size_type n = mat.cols();

        decomposition_ = mat;

        for (DenseMatrix::size_type i = 0; i < n; ++i) {
            for (DenseMatrix::size_type k = i + 1; k < n; ++k) {
                decomposition_(k,i) = decomposition_(k,i) / decomposition_(i,i);
                for (DenseMatrix::size_type j = i + 1; j < n; ++j) {
                    decomposition_(k,j) = decomposition_(k,j) - decomposition_(k,i) * decomposition_(i,j);
                }
            }
        }
    }

    void LU::apply (Vector const& b, Vector& x) const {
        DenseMatrix::size_type const n = decomposition_.rows();

        // 1: solve Ly = b
        Vector y = Vector(n);
        for (DenseMatrix::size_type i = 0; i < n; ++i) {
            DenseMatrix::value_type sum = 0;
            for (DenseMatrix::size_type k = 0; k < i; ++k){
                sum += decomposition_(i,k) * y[k];
            }
            y[i] = b[i] - sum;
        }

        // 2. solve Ux = y
        for (DenseMatrix::size_type i = n - 1; i >= 0 && i < n; --i){
            DenseMatrix::value_type sum = 0;
            for (DenseMatrix::size_type k = i + 1; k < n; ++k){
                sum += decomposition_(i,k) * x[k];
            }
            x[i] = (1 / decomposition_(i,i)) * (y[i] - sum);
        }
        return ;
    }

    void LU::print () {
        DenseMatrix::value_type const zero = 0.0;
        DenseMatrix::value_type const one  = 1.0;
        int const wid = 6;
        int const prec = 2;
        std::cout.setf(std::ios::fixed);
        

        // print the L factor
        std::cout << "L = " << std::endl;
        for (DenseMatrix::size_type i = 0; i < decomposition_.rows(); ++i){
            std::cout << "  [ ";
            for (DenseMatrix::size_type j = 0; j < decomposition_.cols() - 1; ++j){
                if (i >= j){
                    if (i == j){
                        std::cout << std::setw(wid) << std::setprecision(prec) << one << ", ";
                    } else {
                        std::cout << std::setw(wid) << std::setprecision(prec) << decomposition_(i,j) << ", ";
                    }
                } else {
                    std::cout << std::setw(wid) << std::setprecision(prec) << zero << ", ";
                }
            }

            // print last column
            if (i == decomposition_.cols() - 1){
                std::cout << std::setw(wid) << std::setprecision(prec) << one;
            } else {
                std::cout << std::setw(wid) << std::setprecision(prec) << zero;
            }
            std::cout << " ]" << std::endl;
        }

        // print the U factor
        std::cout << "R = " << std::endl;
        for (DenseMatrix::size_type i = 0; i < decomposition_.rows(); ++i){
            std::cout << "  [ ";
            for (DenseMatrix::size_type j = 0; j < decomposition_.cols() - 1; ++j){
                if (i > j){
                    std::cout << std::setw(wid) << std::setprecision(prec) << zero << ", ";
                } else {
                    std::cout << std::setw(wid) << std::setprecision(prec) << decomposition_(i,j) << ", ";
                }
            }

            // print last column
            std::cout << std::setw(wid) << std::setprecision(prec) << decomposition_(i,decomposition_.cols() - 1) << " ]" << std::endl;
        }

    }
    
    /*
    DenseMatrix LU::get () {
        return decomposition_;
    }
    */

} // end namespace scprog
