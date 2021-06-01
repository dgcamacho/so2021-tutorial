#pragma once

#include "DenseMatrix.hh"
#include "Vector.hh"

namespace scprog
{
    class LU {
        public:
            LU (DenseMatrix::size_type const n);

            // decomposing the matrix m, without modifing it
            void compute (DenseMatrix const& mat);

            // apply LU decomposition for solving Ax = LUx = b
            void apply (Vector const& b, Vector& x) const;

            // print the factors of LU decomposition separately
            void print ();

            //DenseMatrix get ();
            
        private:
            DenseMatrix decomposition_; // store the decomposition in this matrix
    };

} // end namespace scprog
