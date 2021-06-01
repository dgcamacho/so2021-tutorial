#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <vector>

namespace scprog
{
    class Vector;

    class DenseMatrix
    {
        public:
            using value_type = double;
            using size_type = std::size_t;
        public:
            // construct empty Matrix
            DenseMatrix():rows_{0}, cols_{0} {}

            // construct zero Matrix with given values
            DenseMatrix(size_type nrows, size_type ncols): rows_{nrows},
                                                           cols_{ncols} {
                data_ = std::vector<value_type>(nrows*ncols);
            }

            // copy constructor
            DenseMatrix(DenseMatrix const& v);

            // access operator
            value_type& operator()(size_type i, size_type j);

            // access operator to ask for specific entry but not change it
            value_type const& operator()(size_type i, 
                                         size_type j) const;
            size_type rows() const;

            size_type cols() const;

            // maximum entry in a given column
            value_type colmax(size_type k) const;

            // maximum entry in a given row
            value_type rowmax(size_type k) const;

            // index of maximum entry in given column
            size_type colargmax(size_type k) const;

            // index of maximum entry in given row
            size_type rowargmax(size_type k) const;

            // calculate y = A*x
            void mv(Vector const& x, Vector& y) const;

            // fill initial matrix with data-vector
            DenseMatrix& fill(std::vector<value_type> data, 
                              size_type const rows, size_type const cols);

            // specific fill-method - initialize identity matrix of given 
            // size
            DenseMatrix& eyes(size_type const rows, size_type const cols);

            DenseMatrix& operator=(DenseMatrix const& that);

        private:
            size_type rows_;
            size_type cols_;
            std::vector<double> data_;
    };
}
