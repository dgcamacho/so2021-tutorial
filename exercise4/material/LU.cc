#include <iostream>

#include "LU.hh"

namespace scprog
{
    using size_t = LU::size_t;
    using real_t = LU::real_t;

    // calculate LU-decomposition of a given matrix m
    void LU::compute(DenseMatrix const& m)
    {
        // store decomposition in a matrix belonging to the class rather than
        // changing the input matrix
        decomposition_ = m;

        // initialize current column-number which is necessary for pivoting
        size_t k = 0;
        for (size_t i = 0; i < m.rows() - 1; ++i) {
            // look for largest entry in column
            size_t imax = m.colargmax(k);
            // swap rows, so that largest column value is used as pivot-
            // element
            if (m(imax, k) == 0) {
                k += 1;
            } else {
                LU::swap_rows(i, imax);  
                
                real_t scale = 0.0;
                // iterate over remaining rows
                for (size_t l = i + 1; l < m.rows(); ++l) {
                    // calculate new matrix entries by scaling with the pivot
                    // element
                    scale = decomposition_(l, k)/decomposition_(i, k);
                    decomposition_(l,k) = scale;
                    // iterate over the remaining columns
                    for (size_t n = k + 1; n < m.cols(); ++n) {
                        decomposition_(l, n) = decomposition_(l, n) -
                                               decomposition_(i, n)*scale;
                     }
                }
                k += 1;
            }
        }
    }

    // solve a given linear system of equations A*x = b for x
    void LU::apply(Vector const& b, Vector& x) const
    {
        // assert whether the system of equations is well-posed in regards to
        // the dimensions
        assert(decomposition_.rows() == x.size());
        assert(decomposition_.cols() == b.size());

        // initialize a rhs-vector to calculate the perturbed b-vector if per-
        // turbations took place because of the choice of pivot-elements
        Vector rhs(b.size());
        if (swapped_) {
            perturbation_.mv(b, rhs);
        } else {
            rhs = b;
        }

        // calculate starting element of forward propagation
        x[0] = b[0];
        // forward propagation
        for (size_t i = 1; i < x.size(); ++i) {
            real_t sum_val = 0.0;
            for (size_t j = 0; j < i; ++j)
                sum_val += decomposition_(i,j)*x[j];
            x[i] = b[i] - sum_val;
        }

        //calculate starting element of backward propagation
        x[x.size() - 1] = x[x.size() - 1]/decomposition_(x.size() - 1, 
                                                         b.size() - 1);
        // backward propagation
        for (size_t i = x.size() - 1; i > 0; --i) {
            real_t sum_val = 0.0;
            for (size_t j = i; j < b.size(); ++j)
                sum_val += decomposition_(i - 1,j)*x[j];
            x[i - 1] = 1/decomposition_(i - 1,i - 1)*(x[i - 1] - sum_val);
        }
}

    // swap rows of the decomposition matrix and the perturbation matrix to 
    // handle the pivoting steps 
    void LU::swap_rows(size_t k, size_t l)
    {
        // check whether rows to change are in right range
        assert((k < decomposition_.rows()) && (l < decomposition_.rows()));
        // check whether rows where swapped before, if not initialize the 
        // perturbation matrix with the necessary size
        if (!swapped_) {

            perturbation_.eyes(decomposition_.rows(), decomposition_.cols());
            swapped_ = 1;
        }
        real_t swp = 0;
        real_t swp_eyes;
        for (size_t j = 0; j < decomposition_.cols(); j ++) {
            swp = decomposition_(k,j);
            swp_eyes = perturbation_(k,j);
            decomposition_(k,j) = decomposition_(l,j);
            perturbation_(k,j) = perturbation_(l,j);
            decomposition_(l,j) = swp;
            perturbation_(l,j) = swp_eyes;
        }
    }
}
