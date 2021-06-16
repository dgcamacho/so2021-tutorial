#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>

#include "Vector.hh"

using namespace scprog;

template <class T>
class CSR {
public:
    // The data type of the matrix entries
    using value_type = T;

    // The data type of the size and indices
    using size_type = std::size_t;

public:
    // construct and initialize with non-zeros representing the number of non-zero elements per row
    CSR (size_type rows, size_type cols, size_type non_zeros)
        : rows_(rows)   // currently not needed
        , cols_(cols)   // currently not needed
        , values_(non_zeros * cols)     // initialized with 0 or 0.0 by default
        , indices_(non_zeros * cols)    // initialized with 0 by default
        , offset_(rows)                 // initialized with 0 by default
    {
    }

    // returns non-zero values of matrix - used for testing (see main function)
    std::vector<value_type> values () {
        return values_;
    }

    // returns columns indices of non-zero values of matrix - used for testing (see main function)
    std::vector<size_type> indices () {
        return indices_;
    }

    // returns number of entries in each row - used for testing (see main function)
    std::vector<size_type> offset () {
        return offset_;
    }

    // access operator for accessing entry at position (i,j)
    value_type operator() (size_type const i, size_type const j) {
        size_type col_entries_before = std::accumulate(offset_.begin(), offset_.begin() + i, 0);
        size_type col_entries = offset_[i];
        
        auto first = indices_.begin() + col_entries_before; // iterator to first column index of row i
        auto last  = first + col_entries;                   // iterator to last column index of row i

        auto pos = std::lower_bound(first, last, j);

        if (pos != last && *pos == j)
            return *(values_.begin() + std::distance(indices_.begin(), pos));
        else
            return 0.0;
    }

    // access operator for accessing entry at position (i,j)
    value_type operator() (size_type const i, size_type const j) const {
        size_type col_entries_before = std::accumulate(offset_.begin(), offset_.begin() + i, 0);
        size_type col_entries = offset_[i];
        
        auto first = indices_.begin() + col_entries_before; // iterator to first column index of row i
        auto last  = first + col_entries;                   // iterator to last column index of row i

        auto pos = std::lower_bound(first, last, j);

        if (pos != last && *pos == j)
            return *(values_.begin() + std::distance(indices_.begin(), pos));
        else
            return 0.0;
    }

    // initalizes entry at position (row, col) with val or overwrites the existing value at this position
    // overwriting with 0 is allowed but will use unnecessary memory
    void set (size_type row, size_type col, value_type val) {        
            size_type col_entries_before = std::accumulate(offset_.begin(), offset_.begin() + row, 0);
            size_type col_entries = offset_[row];
            
            auto first = indices_.begin() + col_entries_before;
            auto last  = first + col_entries;

            auto pos = std::lower_bound(first, last, col);          // pointer to where to insert a new element
            auto pos_index = std::distance(indices_.begin(), pos);  // index of pos in indices vector
    
            if (*pos == col && pos != last) {
                // entry already exists
                *(values_.begin() + pos_index) = val;
            } else if (!(almost_equal(val, 0.0))) {
                // entry does not exist & is non-zero: shift all positions to the right to create space
                if ( values_.back() != 0.0) 
                    throw "value cannot be saved, already too many non zero values existing";
                
                shift_r(indices_, pos);                         // create space for new entry
                shift_r(values_, values_.begin() + pos_index);
                
                *pos = col;                             // insert new column index
                *(values_.begin() + pos_index) = val;   // insert new value

                offset_[row] += 1;      // row has one more element now
            }
    }

    // sets entry at position (row, col) with val or adds val to the existing value at this position
    void add (size_type row, size_type col, value_type val) {
        set(row, col, val + (*this)(row, col));
    }

    void compress () {
        // erases all unnecessary zeros at the end of values_ and indices_
        size_type non_zeros = std::accumulate(offset_.begin(), offset_.end(), 0);
        values_.erase(values_.begin() + non_zeros, values_.end());
        indices_.erase(indices_.begin() + non_zeros, indices_.end());
    }

    void mv (Vector const&x, Vector& y) const {
        size_type entries_before = 0;
        for (size_type i = 0; i < offset_.size(); ++i) {
            // ith row of csr matrix corresponds to ith entry of resulting vector
            size_type col_entries = offset_[i];

            value_type sum = 0;
            for (size_type j = entries_before; j < entries_before + col_entries; ++j) {
                // j corresponds to the indices_[j]th column of csr matrix
                sum += (*this)(i, indices_[j]) * x[indices_[j]];
            }
            y[i] = sum;

            entries_before += offset_[i];
        }
    }

    // prints the matrix as "dense matrix"
    void print () {
        int const wid = 6;
        int const prec = 2;
        std::cout.setf(std::ios::fixed);

        for (size_type i = 0; i < rows_; ++i){
            std::cout << "  [ ";
            for (size_type j = 0; j < cols_ - 1; ++j){
                std::cout << std::setw(wid) << std::setprecision(prec) << (*this)(i,j) << ", ";
            }
            std::cout << std::setw(wid) << std::setprecision(prec) << (*this)(i, cols_ - 1) << " ]" << std::endl;
        }
    }


private:
    // shifting all entries starting at position pos to the right; the last element is lost; empty position is initalized with 0
    template <class E>
    void shift_r (std::vector<E> &v, typename std::vector<E>::iterator pos) {
        typename std::vector<E>::iterator end = v.end() - 1; // iterator to last element in v
        for (size_type i = 0; end - i != pos; ++i){
            *(end - i) = *(end - i - 1);
        }
        *pos = 0;
    }

    template <class E>
    bool almost_equal(E x, E y) {
        return std::abs(x - y) < 0.001;
    }
    
private:
    std::vector<value_type> values_;
    std::vector<size_type> indices_;
    std::vector<size_type> offset_;

    size_type rows_;    // currently not needed
    size_type cols_;    // currently not needed
};




// prints a std::vector
template <class T>
void print (std::vector<T> v){
    std::cout << "[ ";
    for (unsigned int i = 0; i < v.size(); ++i){
        std::cout << v[i] << ", ";
    }
    std::cout << "]" << std::endl;
}



int main () {

    // EXAMPLE of a sparse matrix
    std::cout << "---- EXAMPLE OF A SPARSE MATRIX ----" << std::endl;
   
    CSR<double> example_matrix(3, 4, 3);
    example_matrix.set(0,2,1);
    example_matrix.set(1,0,2);
    example_matrix.set(1,1,5);
    example_matrix.set(2,1,3);
    example_matrix.set(2,3,6);

    example_matrix.add(0,2,5);

    std::cout << "offset  = ";
    print(example_matrix.offset());

    std::cout << "indices = ";
    print(example_matrix.indices());
    
    std::cout << "values  = ";
    print(example_matrix.values());

    std::cout << "\n";

    std::cout << "COMPRESSING ..." << std::endl;
    example_matrix.compress();

    std::cout << "offset  = ";
    print(example_matrix.offset());

    std::cout << "indices = ";
    print(example_matrix.indices());
    
    std::cout << "values  = ";
    print(example_matrix.values());

    std::cout << "\n";

    std::cout << "A = " << std::endl;
    example_matrix.print();

    Vector example_vector = Vector(4); 
    example_vector[0] = 1;
    example_vector[1] = 1;
    example_vector[2] = 1;
    example_vector[3] = 1;

    Vector result = Vector(3);

    std::cout << "\nMATRIX VECTOR PRODUCT" << std::endl;
    example_matrix.mv(example_vector, result);
    
    std::cout << "A * (1,1,1,1) = ";
    result.print();

    std::cout << "\n... done." << std::endl;

    return 1;
}