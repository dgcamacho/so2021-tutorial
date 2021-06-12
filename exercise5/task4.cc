#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>
#include "../exercise4/material/Vector.hh"

namespace scprog
{
    // forward declaration
    class Vector;

    template <class T>
    class CRSMatrix
    {
    public:
    // The data type of the matrix entries
    using value_type = T;

    // The data type of the size and indices
    using size_type = std::size_t;

    public:
    // construct and initialize the matrix of size rows x cols
    CRSMatrix (size_type rows, size_type cols, size_type max_non_zeros);

    // mutable access to the matrix entries
    value_type operator() (size_type i, size_type j);

    // const access to the matrix entries
    value_type const operator() (size_type i, size_type j) const;

    // return the number of rows
    size_type rows () const;

    // return the number of columns
    size_type cols () const;

    // set a nonzero entry at (i,j) in the matrix (replace existing value)
    void set (size_type i, size_type j, value_type value);

    // get the value at (i, j) before the matrix got compressed
    value_type get (size_t i, size_t j);

    // add a nonzero entry at (i,j) to the matrix
    void add (size_type i, size_type j, value_type value);

    // remove all gaps and zeros in the internal storage
    void compress (); 

    // matrix-vector product y = A*x
    void mv (Vector const& x, Vector& y) const;

    void print_uncompressed ();

    void print ();

    private:
    size_type binary_search (size_type const index, size_type& left, size_type& right);

    private:
    size_type minus_one;
    std::size_t rows_;
    std::size_t cols_;
    std::size_t max_non_zeros_;
    std::vector<size_t> indices_;
    std::vector<value_type> values_;
    std::vector<size_t> offset_;

    };

    template<class T>
    CRSMatrix<T>::CRSMatrix (size_type rows, size_type cols, size_type max_non_zeros) 
          : rows_(rows)
          , cols_(cols)
          , max_non_zeros_(max_non_zeros)
          , minus_one(rows*max_non_zeros)
          , indices_(rows*max_non_zeros,0.0)
          , values_(rows*max_non_zeros,0.0)
          , offset_(rows,0.0)
    { }
    
    // mutable access to the matrix entries
    template<class T>
    typename CRSMatrix<T>::value_type CRSMatrix<T>::operator() (size_type i, size_type j) {
        int upper_bound = offset_[i+1];
        if (i == rows_ - 1) {
            upper_bound = values_.size();
        }

        value_type matrix_entry = 0;
        for (size_type ix = offset_[i]; ix < upper_bound; ++ix) {
            if (indices_[ix] == j) {
                matrix_entry = values_[ix];
            }
        }
        return matrix_entry;
    }

    // const access to the matrix entries
    template<class T>
    typename CRSMatrix<T>::value_type const CRSMatrix<T>::operator() (size_type i, size_type j) const {
        int upper_bound = offset_[i+1];
        if (i == rows_ - 1) {
            upper_bound = values_.size();
        }

        value_type matrix_entry = 0;
        for (size_type ix = offset_[i]; ix < upper_bound; ++ix) {
            if (indices_[ix] == j) {
                matrix_entry = values_[ix];
            }
        }
        return matrix_entry;
    }

    template<class T>
    typename CRSMatrix<T>::size_type CRSMatrix<T>::rows () const {
        return rows_;
    }

    template<class T>
    typename CRSMatrix<T>::size_type CRSMatrix<T>::cols () const {
        return cols_;
    }
    
    // Binary search: finds the position of 'index' which is stored in parameter 'left' after leaving the function 
    template<class T>
    typename CRSMatrix<T>::size_type CRSMatrix<T>::binary_search (size_type const index, size_type& left, size_type& right) {
        // if the value is the first one to be set in this row (offset is 0)
        if (left == right) 
            return minus_one;

        // only repeat while left < right and not <= to make sure that the 
        // indices left an right won't overlap
        while (left < right) {
            int mid = left + (right - left) / 2;

            if (indices_[mid] == index) {
                return mid;
            } else if (indices_[mid] < index) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        if (left == right) {
            int mid = left;
            if (indices_[mid] == index) {
                return mid;
            }
        }

        return minus_one;
    }

    // add a nonzero entry at (i,j) to the matrix
    template<class T>
    void CRSMatrix<T>::set (size_type i, size_type j, value_type value) {
        if (i > rows_ - 1 || j > cols_) {
            std::cout << "ERROR: index out of bounds" << std::endl;
            return;
        }
        if (std::abs(value) < std::numeric_limits<double>::epsilon()) {
            std::cout << "ERROR: value must not be zero" << std::endl;
            return;
        }

        size_t left = i * max_non_zeros_;   // index of first value in indices_ and values_
        size_t right = left + offset_[i];   // index of last value in indices_ and values_
        
        // if the value is the first one to be set in this row (offset is 0)
        if (left == right) {
            indices_[right] = j;
            values_[right] = value;
            offset_[i] += 1;
            return;
        }

        // store the right index for later use
        size_type last = right;

        // binary search, position where to set new entry will be stored in 'right'
        size_type insert_index = binary_search(j, left, right);

        // if the index already exists
        if (insert_index != minus_one) {
            values_[insert_index] = value;
            return;
        }

        // shift values to the right
        for (size_t k = last; k > right; --k) {
            indices_[k] = indices_[k-1];
            values_[k] = values_[k-1];
            values_[k-1] = 0;
        }

        // insert new index and value, and update the corresponding offset
        indices_[left] = j;
        values_[left] = value;
        offset_[i] += 1;
    }

    // get the value at (i, j) before the matrix got compressed
    template<class T>
    typename CRSMatrix<T>::value_type CRSMatrix<T>::get (size_t i, size_t j) {
        size_t left = i * max_non_zeros_;   // index of first value in indices_ and values_
        size_t right = left + offset_[i];   // index of last value in indices_ and values_

        // binary search, position where to set new entry will be stored in 'right'
        size_t insert_index = binary_search(j, left, right);

        // if the index does not yet exist
        if (insert_index == minus_one)
            return 0;

        // else: index exists already, so return the value at this position
        return values_[insert_index];
    }

    // set a nonzero entry at (i,j) in the matrix (replace existing value)
    template<class T>
    void CRSMatrix<T>::add (size_type i, size_type j, value_type value) {
        if (i > rows_ - 1 || j > cols_) {
            std::cout << "ERROR: index out of bounds" << std::endl;
            return;
        }
        if (std::abs(value) < std::numeric_limits<double>::epsilon()) {
            std::cout << "ERROR: value must not be zero" << std::endl;
            return;
        }

        // to avoid copying code, use the implemented set and get functions for adding a value
        (*this).set(i, j, value + (*this).get(i, j));
    }

    // remove all gaps and zeros in the internal storage
    template<class T>
    void CRSMatrix<T>::compress () {
        // delete all not necessary entries from values_ and indices_      
        for (int row = rows_-1; row >= 0; --row) {
            for (size_type i = offset_[row]; i < cols_; ++i) {
                indices_.erase(indices_.begin()+row*cols_+offset_[row]);
                values_.erase(values_.begin()+row*cols_+offset_[row]);
            }
        }
        
        // update the offset_ vector
        size_type last_sum = 0, sum = 0;
        for (int ix = 0; ix < offset_.size()-1; ++ix) {
            sum += offset_[ix];
            offset_[ix] = last_sum;
            last_sum = sum;
        }
        offset_[offset_.size()-1] = sum;
    } 

    // matrix-vector product y = A*x
    template<class T>
    void CRSMatrix<T>::mv (Vector const& x, Vector& y) const {
        for (int i=0; i<rows_; ++i) {
            y[i] = 0;
            for (int j=0; j<cols_; ++j) {
            y[i] += (*this)(i,j) * x[j];
            }
        }
    }
    
    // print matrix on terminal
    template<class T>
    void CRSMatrix<T>::print_uncompressed () {
        std::cout << "\n\nIndices: \n";
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < max_non_zeros_; ++j) {
                std::cout << std::setprecision(3) << std::setw(6) << indices_[i*max_non_zeros_ + j]   << " ";
            }
            std::cout << std::endl;            
        }
        std::cout << "\nValues: \n";
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < max_non_zeros_; ++j) {
                std::cout << std::setprecision(3) << std::setw(6) << values_[i*max_non_zeros_ + j]   << " ";
            }
            std::cout << std::endl;   
        }
        std::cout << "\nOffset:   ";
        for (int i = 0; i < rows_; ++i) {
            std::cout << offset_[i]<< "    ";
        }
        std::cout << std::endl;
    } 

    // print matrix on terminal
    template<class T>
    void CRSMatrix<T>::print () {
        for (int i=0; i<rows_; ++i) {
            for (int j=0; j<cols_; ++j) {
                value_type matrix_entry = this->operator()(i,j);
                std::cout << std::setprecision(3) << std::setw(6) << matrix_entry  << " ";
            }
            std::cout << std::endl;
        }
    }

} // end of namespace scprog

using namespace scprog;

int main () {
    CRSMatrix<double> matrix = CRSMatrix<double>(3,3,3);
    matrix.set(0,0,2.0);
    matrix.set(1,2,-1.0);
    matrix.set(1,0,-1.0);
    matrix.set(0,1,-1.0);
    matrix.set(2,1,-1.0);
    matrix.add(2,2,1.0);
    matrix.add(2,2,1.0);
    std::cout << "\nUncompressed output:\n";
    matrix.print_uncompressed();

    matrix.compress();

    std::cout << "\n\n\nTest the implementation of the CRSMatrix\n\nM =\n"; 
    matrix.print();

    // initialize the rhs vector b
    Vector x = Vector(3);
    x[0] = x[1] = x[2] = 1;
    std::cout << "\nx = ";
    x.print();

    Vector y = Vector(3);
    matrix.mv(x, y);
    std::cout << "\ny = ";
    y.print();
}