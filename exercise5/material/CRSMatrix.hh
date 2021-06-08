#pragma once

#include <cassert>
#include <iostream>
#include <vector>
#include "Vector.hh"

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
                std::cout << "Here comes the offset-check " << offset_[i] 
                          << " Passed? " << (offset_[i] < nmax_nonzero_)
                          << std::endl;
                auto first = std::next(indices_.begin(), i*nmax_nonzero_);
                auto last = std::next(first, offset_[i]);

                auto it = i*nmax_nonzero_ + binary_search(first, last, j);

                if (j < indices_[it]) {
                    shift(i);

                    offset_[i] += 1;

                    values_[it] = value_type(0);

                } else if (values_[it] == value_type(0)) {
                    offset_[i] += 1;
                }
                indices_[it] = j;
                values_[it] += value;
            }

            void set(size_type i, size_type j, value_type value)
            {
                std::cout << "Here comes the offset-check " << offset_[i] 
                          << " Passed? " << (offset_[i] < nmax_nonzero_)
                          << std::endl;
                auto first = std::next(indices_.begin(), i*nmax_nonzero_);
                auto last = std::next(first, offset_[i]);

                auto it = i*nmax_nonzero_ + binary_search(first, last, j);

                if (j < indices_[it]) {
                    shift(i);
                    
                    offset_[i] += 1;
                } else if (values_[it] == value_type(0)) {
                    offset_[i] += 1;
                }
                indices_[it] = j;
                values_[it] = value;       
            }

            void compress()
            {
                                
                for (size_type k = indices_.size(); k > 0; --k){
                    if (indices_[k - 1] == size_type(0) && 
                            values_[k - 1] == value_type(0)) {
                        indices_.erase(indices_.begin() + k - 1);
                        values_.erase(values_.begin() + k - 1);

                    }
                } 
            }

            void mv(Vector const &x, Vector& y)
            {
                assert(x.size() == cols_ && y.size() == rows_);
                for (size_type i = 0; i < rows_; ++i) {
                    if (offset_[i] == size_type(0)) {
                        y[i] = value_type(0);
                    } else {
                        size_type lower_bound = offset_[i - 1];
                        size_type upper_bound = lower_bound + offset_[i];
                        
                        for (size_type j = lower_bound; j < upper_bound; ++j) {
                            y[i] += values_[j] * x[indices_[j]];
                        }
                    }
                }
            }

        private:
            size_type rows_;
            size_type cols_;
            size_type nmax_nonzero_;
            std::vector<size_type> indices_;
            std::vector<value_type> values_;
            std::vector<size_type> offset_;

            auto binary_search(std::vector<size_type>::iterator first, 
                               std::vector<size_type>::iterator last,
                               size_type wanted) 
            {
                assert(last < indices_.end());
                auto it = std::lower_bound(first, last, wanted);
                return it - first;
            
            }

            void shift(size_type i)
            {
                for (size_type k = (i+1)*nmax_nonzero_; 
                        k > i*nmax_nonzero_ - 1; --k) {
                    if (indices_[k] == size_type(0) && 
                        values_[k] == value_type(0)) {
                        if (indices_[k - 1] != size_type(0) && 
                            values_[k - 1] != value_type(0)) {
                            indices_[k] = indices_[k - 1];
                            values_[k] = values_[k - 1];
                            indices_[k - 1] = size_type(0);
                            values_[k - 1] = value_type(0);
                        }
                    }
                }
            }
    };
}

