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
            explicit CRSMatrix() = default;
            // constructor with given row-,col-size and maximum number of
            // non-zero entries per row
            explicit CRSMatrix(size_type nrows, size_type ncols, 
                               size_type nmax_nonzero): 
                                             rows_{nrows}, 
                                             cols_{ncols}, 
                                             nmax_nonzero_{nmax_nonzero},
                                             indices_(nrows*nmax_nonzero),
                                             values_(nrows*nmax_nonzero), 
                                             offset_(nrows) 
                                             {}
            
        // class functions
        public:
            // returns number of all rows, also 0-rows
            size_type rows() const 
            {
                return rows_;
            }

            // returns number of all columns, also 0-columns
            size_type cols() const
            {
                return cols_;
            }

            // add a value to a certain position in the matrix
            void add(size_type i, size_type j, value_type value)
            {
                
                auto first = std::next(indices_.begin(), i*nmax_nonzero_);
                auto last = std::next(first, offset_[i]);

                //index of the position where value shall be added
                auto it = i*nmax_nonzero_ + binary_search(first, last, j);

                // if the index stored at the wanted position is larger than 
                // the one to be added, the stored index has to be shifted to 
                // the right
                if (j < indices_[it]) {
                    // if the max no. of non-zero entries is already reached, 
                    // the shift is not allowed! Otw. shift and increase value
                    // of offset_ at row i AND reset value at wanted index
                    if (offset_test(i)) {
                        shift(i);

                        offset_[i] += 1;

                        values_[it] = value_type(0);
                    } else {
                        std::cout << "This row already contains max no. of "
                                  << "non-zero entries!" << std::endl;
                        abort();
                    }

                } else if (values_[it] == value_type(0)) {
                    // if value at wanted index is zero (no entry set or added)
                    // and max no. of non-zero entries is not reached, increase
                    // offset_ at row i.
                    if (offset_test(i)) {
                        offset_[i] += 1;
                    } else {
                        std::cout << "This row already contains max no. of "
                                  << "non-zero entries!" << std::endl;
                        abort();
                    }
                }
                indices_[it] = j;
                values_[it] += value;
            }

            // set a certain entry of the matrix to the passed value
            void set(size_type i, size_type j, value_type value)
            {
                auto first = std::next(indices_.begin(), i*nmax_nonzero_);
                auto last = std::next(first, offset_[i]);

                // index of the position where a value shall be set
                auto it = i*nmax_nonzero_ + binary_search(first, last, j);

                // if the index stored at the wanted position is larger than 
                // the one to be inserted, the stored index has to be shifted
                // to the right
                if (j < indices_[it]) {
                    // if the max no. of non-zero entries is already reached,
                    // the shift is not allowed! Otw. shift and increase value
                    // of offset_ at row i
                    if (offset_test(i)) {
                        shift(i);
                    
                        offset_[i] += 1;
                    } else {
                        std::cout << "This row already contains max no. of "
                                  << "non-zero entries!" << std::endl;
                        abort();
                    }
                } else if (values_[it] == value_type(0)) {
                    // if value at wanted index is zero (no entry set or added)
                    // and max no. of non-zero entries is not reached, increase
                    // offset_ at row i.
                    if (offset_test(i)) {
                        offset_[i] += 1;
                    } else {
                        std::cout << "This row already contains max no. of "
                                  << "non-zero entries!" << std::endl;
                        abort();                       
                    }
                }
                indices_[it] = j;
                values_[it] = value;       
            }

            // delete all zero-entries from the indices_ and values_ vectors
            void compress()
            {
                // iterate reversively over all elements to not get size prob-
                // lems because of deleted entries
                for (size_type k = indices_.size(); k > 0; --k){
                    if (indices_[k - 1] == size_type(0) && 
                            values_[k - 1] == value_type(0)) {
                        indices_.erase(indices_.begin() + k - 1);
                        values_.erase(values_.begin() + k - 1);

                    }
                }
            }

            // calculate y = A*x
            void mv(Vector const &x, Vector& y)
            {
                // check for dimensions
                assert(x.size() == cols_ && y.size() == rows_);
                for (size_type i = 0; i < rows_; ++i) {
                    // if the row does not contain non-zero entries, the y-val
                    // is zero
                    if (offset_[i] == size_type(0)) {
                        y[i] = value_type(0);
                    } else {
                        // catching first row distance with conditional op.
                        size_type lower_bound = (i != 0) ? offset_[i - 1] : 0;
                        size_type upper_bound = lower_bound + offset_[i];
                        
                        for (size_type j = lower_bound; j < upper_bound; ++j) {
                            y[i] += values_[j] * x[indices_[j]];
                        }
                    }
                }
            }

        private:
            size_type rows_;                 // number of all rows
            size_type cols_;                 // number of all cols
            size_type nmax_nonzero_;         // number of max. non-zero entries
                                             // per row
            std::vector<size_type> indices_; // indices where values != 0
            std::vector<value_type> values_; // non-zero values
            std::vector<size_type> offset_;  // no. of non-zero entries per row

            // searches for the first element in a range of elements that is
            // not less than the wanted type.
            auto binary_search(std::vector<size_type>::iterator first, 
                               std::vector<size_type>::iterator last,
                               size_type wanted) 
            {
                assert(last < indices_.end());
                auto it = std::lower_bound(first, last, wanted);

                // returning the distance of the first pointer and the pointer
                // corresponding to the wanted value, which is usable as 
                // size_type
                return it - first;
            
            }

            // shift elements of a given row to a neighbouring non-zero entry
            void shift(size_type i)
            {
                // iterate reversively over all column-elements in the given 
                // row
                for (size_type k = (i+1)*nmax_nonzero_; 
                        k > i*nmax_nonzero_ - 1; --k) {
                    // if current entry is zero-entry, shift the left entry
                    // into current entry
                    if (indices_[k] == size_type(0) && 
                        values_[k] == value_type(0)) {
                        if (indices_[k - 1] != size_type(0) && 
                            values_[k - 1] != value_type(0)) {
                            indices_[k] = indices_[k - 1];
                            values_[k] = values_[k - 1];

                            // clear left entries, so that next-to-left entry
                            // can be shifted again
                            indices_[k - 1] = size_type(0);
                            values_[k - 1] = value_type(0);
                        }
                    }
                }
            }

            // checks whether the maximun no. of non-zero entries is reached
            bool offset_test(size_type i) 
            {
                return (offset_[i] < nmax_nonzero_) ? 1 : 0;
            }
    };
}

