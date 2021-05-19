#pragma once

#include <cassert>
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
            DenseMatrix():rows_{0}, cols_{0} {}

            DenseMatrix(size_type nrows, size_type ncols): rows_{nrows},
                                                           cols_{ncols} {
                data_ = std::vector<value_type>(nrows*ncols);
            }
            DenseMatrix(DenseMatrix const& v);

            value_type& operator()(size_type i, size_type j);

            value_type const& operator()(size_type i, 
                                         size_type j) const;
            size_type rows() const;

            size_type cols() const;

            void mv(Vector const& x, Vector& y) const;

        private:
            size_type rows_;
            size_type cols_;
            std::vector<double> data_;
    };
}
