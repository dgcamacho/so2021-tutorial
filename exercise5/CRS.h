#pragma once

#include <cassert>
#include <iostream>
#include <vector>
#include "Vector.hh"

namespace scprog
{
    // Forward declaration
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
                             values_{0}, offset_{0}, row_pointer_{0}, nonzero_entries_{0} {}
        // constructor with given row-,col-size and maximum number of
        // non-zero entries per row
        explicit CRSMatrix(size_type nrows, size_type ncols,
                           size_type nmax_nonzero):
                rows_{nrows}, cols_{ncols},
                nmax_nonzero_{nmax_nonzero},
                indices_(nrows*nmax_nonzero),
                values_(nrows*nmax_nonzero),
                offset_(nrows),
                row_pointer_(nrows),
                nonzero_entries_{0}
                {}

        // Class functions
    public:

        size_type rows() const
        {
          return rows_;
        }

        size_type cols() const
        {
          return cols_;
        }

        // Add a value on given entry. If the entry was previously unset, it is set
        void add(size_type i, size_type j, value_type value){
          if (check_overflow(i, j)){
          auto aim = find_index(i, j);
          if(value_exists(i, j))
            {values_[aim] += value;}
          else{
            set(i, j, value);
          }
        }
        }

        // Set an entry to given value
        void set(size_type i, size_type j, value_type value){
          {
            auto aim = find_index(i, j);
            if (value_exists(i, j)) { values_[aim] = value; }
            else {
            for (auto k = nonzero_entries_; k > aim; --k) {
              values_[k] = values_[k - 1];
              indices_[k] = indices_[k - 1];
            }
            offset_[i] += 1;
            update_row_pointer(i);
            nonzero_entries_ += 1;
            indices_[aim] = j;
            values_[aim] = value;
            }
          }
        }

        // Remove all unfilled elements
        void compress(){
          this->indices_.resize(this->nonzero_entries_);
          this->values_.resize(this->nonzero_entries_);
        };

        // Matrix-vector multiplication
        // todo use Boost library for zip expression
        void mv(scprog::Vector const &x, scprog::Vector& y){
            assert(cols_ == x.size() && x.size() == y.size());
            unsigned k{0}, current_row{0};
            for (auto entry : indices_)
            {
              current_row < k ? ++current_row : 0;
              y[current_row] += values_[k] * x[entry];
              ++k; // Not very elegant, yet easy solution to keep track of index
            }
          }

        // Check whether there exist a value
        bool value_exists(size_type i, size_type j){
          bool value_exists = false;
          // Iterate over indices_ and get value_ by index. Could use the zip function from boost instead
          for (auto x = row_pointer_[i]; x < row_pointer_[(i + 1)]; ++i){
            indices_[row_pointer_[i] + x] == j ? value_exists = true : 0;
          }
          return value_exists;
        }

        // Const access to value
        value_type const& at(size_type i, size_type j) const {
          return values_[find_index(i, j)];
        }

        // Mutable access to value
        value_type& at(size_type& i, size_type j){
          return values_[find_index(i, j)];
        }

    private:
        size_type rows_;
        size_type cols_;
        size_type nmax_nonzero_;
        size_type nonzero_entries_;
        std::vector<size_type> indices_;
        std::vector<value_type> values_;
        std::vector<size_type> offset_;
        std::vector<size_type> row_pointer_;

        // Update row pointer on insertion
        void update_row_pointer(size_type n){
          for (size_type i = n + 1; i < rows_; ++i){
            row_pointer_[i] += 1;
          }
        }

        // Find index of given matrix entry in values_/indices_ vector
        size_type find_index(size_type i, size_type j){
          auto first = indices_.begin() + row_pointer_[i];
          auto last = first + offset_[i];
          auto lower = std::lower_bound(first, last, j);
          auto aim = lower - first + row_pointer_[i];
          return aim;
        }

        // Check whether a column is already filled
        bool check_overflow(size_type i, size_type j) const{
          if(offset_[i] >= nmax_nonzero_){
          #pragma message("Warning: Too many entries in current line. Omitting last entry.")
            return false;
          }
          return true;
        }
    };
}
