// Implement a sparse matrix in CRS Format. Therefore, write a class `CRSMatrix<T>` parametrized with the element type `T` that provides the following
// interface:

// - A constructor with number of rows and number of columns and a third argument for the maximal
//   number of nonzero entries per row.
// - A type alias `value_type = T` (and a `size_type` alias as well)
// - A function `void add (size_type i, size_type j, value_type value)` to add a nonzero entry at `(i,j)` to
//   the matrix. If an entry already exists at this position, the values should be added up.
// - A function `void set (size_type i, size_type j, value_type value)` to add a nonzero entry at `(i,j)` to
//   the matrix. If an entry already exists at this position, the values should be replaced by the given `value`.
// - A function `void compress ()` to remove all gaps and zeros in the internal storage.
// - Matrix-Vector multiplication `y = A*x` by `void mv (Vector const& x, Vector& y) const`.

// The strategy to implement insertion is as follows:

// 1. Create vectors `indices` and `values` of size *(maximum number of nonzeros per row) x (number of rows)* and type `std::vector<...>`
// 2. Create a vector `offset` of size *(number of rows)* and type `std::vector<...>` that contains the number of column entries already stored in each row, thus initialized to 0.
// 3. On insertion by `add` or `set` go to the corresponding position of the row in `indices` and `values` and traverse all stored column
//    indices to find the position where to insert a new entry. Therefore, we assume that the column indices
//    are sorted in each row. Thus, you can use a binary-search to find the position where to insert a new entry.
//    Move all entries with higher indices one position to the right and insert the new index (or if the
//    column index exists already, just modify the value).
// 4. Update the `offset` vector by increasing the number of column values by one (or leave it untouched if the
//    existing value was just modified)
// 5. On `compress()` all three vectors should be transformed into the final format. Therefore traverse
//    row-wise, accumulate the row-sizes to get the offset, and collect only those entries in `indices` and `values`
//    that are stored in each row.
#pragma once

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <tuple>
#include <vector>

#include "BinarySearch.cc"

template <class value_type>
class CRSMatrix{
    using size_type = std::size_t;
    
    public:
        CRSMatrix(size_type nr, size_type nc, size_type max_nonzero_per_row)
            : _nr(nr), _nc(nc), _max_nz(max_nonzero_per_row),
                _indices(_nr * _max_nz, 0),
                _values(_nr * _max_nz, 0),
                _offset(_nr, 0)
            { };

        // wrapper for general binary search
        // RETURNS (row_offset, index from row_offset of element, element_exists)
        std::tuple<size_type, size_type, bool> search_for_element(size_type row, size_type col){
            
            // std::cout << "In search_for_element, " << row << ' ' << col << "\n";
            
            // calculate part of _indices belonging to 'row'
            // which ranges from row_offset to row_offset + _offset[row] - 1
            size_type row_offset = 0;
            for (size_type i = 0; i < row; ++i) {
                row_offset += _offset[i];
            }
            
            if (_offset[row] == 0){
                return {row_offset, 0, false};
            }
            // try to find the column-index in the _indices array for the correct row
            auto [index, exists_flag] = binary_search(
                _indices, row_offset, row_offset + _offset[row] - 1, col);
            
            return {row_offset, index - row_offset, exists_flag};
        }

        // element access
        value_type operator() (size_type row, size_type col){
            auto [row_offset, index, exists_flag] = search_for_element(row, col);

            // return value if found
            if (exists_flag){
                return _values[row_offset + index];
            }
            else {
                return 0;
            }
        }

        // add to element
        void add(size_type row, size_type col, value_type value) {
            // adding 0 does not change anything
            if (value == 0) {
                return;
            }
            auto [row_offset, index, exists_flag] = search_for_element(row, col);

            if (index > _max_nz) {
                std::cout << row << " = row.\n";
                throw std::invalid_argument("Zu viele Elemente in einer Zeile.");
            }

            if (exists_flag == true){
                // increment value and delete associated indices if result is 0
                if ((_values[row_offset + index] += value) == 0) {
                    _indices.erase(_indices.begin() + row_offset + index);
                    _values.erase(_values.begin() + row_offset + index);
                    _offset[row] -= 1;
                }
            }
            else {
                auto it = _values.begin() + row_offset + index;
                _values.insert(it, value);
                auto it2 = _indices.begin() + row_offset + index;
                _indices.insert(it2, col);
                _offset[row] += 1;
            }
        }

        // set element
        void set(size_type row, size_type col, value_type value) {
            auto [row_offset, index, exists_flag] = search_for_element(row, col);


            if (index > _max_nz) {
                std::cout << row << " = row.\n";
                throw std::invalid_argument("Zu viele Elemente in einer Zeile.");
            }
            if (exists_flag == true){
                // set value and delete associated indices if result is 0
                if ((_values[row_offset + index] = value) == 0) {
                    _indices.erase(_indices.begin() + row_offset + index);
                    _values.erase(_values.begin() + row_offset + index);
                    _offset[row] -= 1;
                }
            }
            else {
                // do not insert zero values
                if (value != 0)
                {
                    auto it = _values.begin() + row_offset + index;
                    _values.insert(it, value);
                    auto it2 = _indices.begin() + row_offset + index;
                    _indices.insert(it2, col);
                    _offset[row] += 1;
                }
            }
        }

        // compress storage
        void compress() {
            // calculate actual maximum nonzero size
            size_type new_max_nz = 0;
            for (size_type i = 0; i < _nr; ++i)
            {
                new_max_nz = std::max(new_max_nz, _offset[i]);
            }
            _max_nz = new_max_nz;
            // reduce the vectors to the appropriate sizes
            _indices = std::vector<size_type>(_indices.begin(), _indices.begin() + (_nr * _max_nz));
            _values = std::vector<value_type>(_values.begin(), _values.begin() + (_nr * _max_nz));
        }

        // increase the storage vectors to allow for a larger number of nonzeros
        void increase_max_nonzeros(size_type new_max_nz) {
            // allocation of larger arrays will be done automatically by std::vector's insert
            // we only ever traverse the arrays front to back (via _offset),
            // so there is no need to actually allocate more memory here
            if (new_max_nz < _max_nz){
                std::cout << "I will not decrease max_nz. Use compress instead.\n";
            }
            else {
                _max_nz = new_max_nz;    
            }
        }

        size_type max_nz(){
            return _max_nz;
        }

        size_type nc(){
            return _nc;
        }

        size_type nr(){
            return _nr;
        }
        // y := A * x
        void mv(std::vector<value_type> const& x, std::vector<value_type>& y);

        void print() {
            std::cout << "Printing current state.\n_indices = ";
            for (int i = 0; i < _indices.size(); ++i)
            {
                std::cout << _indices[i] << ' ';
            }
            std::cout << '\n';

            std::cout << "_offset = ";
            for (int i = 0; i < _offset.size(); ++i)
            {
                std::cout << _offset[i] << ' ';
            }
            std::cout << '\n';

            std::cout << "_values = ";
            for (int i = 0; i < _values.size(); ++i)
            {
                std::cout << _values[i] << ' ';
            }
            std::cout << '\n';

            size_type running_offset = 0;
            for (size_type i = 0; i < _nr; ++i)
            {
                for (size_type j = 0; j < _offset[i]; ++j)
                {
                    std::cout << '(' << i << ", " << _indices[j + running_offset] << ") : " << _values[j + running_offset] << "\n";
                }
                running_offset += _offset[i];
            }
        }

        void print_nonsparse() {
            for (size_type i = 0; i < _nc; ++i)
            {
                for (size_type j = 0; j < _nr; ++j)
                {
                    std::cout << (*this)(i, j) << " ";
                }
                std::cout << '\n';
            }
        }

    private:
        size_type _max_nz;
        size_type _nr;
        size_type _nc;
        std::vector<size_type> _indices;
        std::vector<size_type> _offset;
        std::vector<value_type> _values;
     
};
