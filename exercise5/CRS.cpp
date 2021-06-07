#pragma one

#include <cassert>
#include <iostream>
#include <vector>

namespace scprog
{
    class Vector;

    template <typename T>
    class CRSMatrix
    {
        // type aliases
    public:
        using size_type = std::size_t;

        using value_type = T;

        // constructors
    public:
        // default constructors
        explicit CRSMatrix():rows_{0}, cols_{0}, indices_{0},
                             values_{0}, offset_{0} {}
        // constructor with given row-,col-size and maximum number of
        // non-zero entries per row
        explicit CRSMatrix(size_type nrows, size_type ncols,
                           size_type nmax_nonzero):
                rows_{nrows}, cols_{ncols},
                nmax_nonzero_{nmax_nonzero},
                indices_(nrows*nmax_nonzero),
                values_(nrows*nmax_nonzero),
                offset_(nrows) {}

        // class functions
    public:

        size_type rows() const
        {
          return rows_;
        }

        size_type cols() const
        {
          return cols_;
        }

        void add(size_type i, size_type j, value_type value)
        {
          auto first = std::next(indices_.begin(), i*nmax_nonzero_);
          auto last = std::next(first, offset_[i]);
          //std::cout << first << " " << last << std::endl;
          for (auto k = first; k < last; ++k){
            std::cout << indices_[k] << std::endl;
          }

        }

        void set(size_type i, size_type j, value_type value);

        void compress();

        void mv(Vector const &x, Vector& y);
    private:
        size_type rows_;
        size_type cols_;
        size_type nmax_nonzero_;
        std::vector<value_type> indices_;
        std::vector<value_type> values_;
        std::vector<value_type> offset_;
    };
}
