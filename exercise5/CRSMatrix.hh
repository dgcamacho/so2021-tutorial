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

#include <vector>
#include <tuple>
#include "BinarySearch.cc"

template <class T>
class CRSMatrix{
    using value_type = T;
    using size_type = std::size_t;
    
    public:
        CRSMatrix(int nr, int nc, int max_nonzero_per_row)
            : _nr(nr), _nc(nc), _max_nz(max_nonzero_per_row),
                _indices(_nr * _max_nz, 0),
                _values(_nr * _max_nz, 0),
                _offset(_nr, 0) {};

        // wrapper for general binary search
        // RETURNS (row_offset, index from row_offset of element, element_exists)
        std::tuple<size_type, size_type, bool> search_for_element(size_type row, size_type col){
            // calculate part of _indices belonging to 'row'
            // which ranges from row_offset to row_offset + _offset[row] - 1
            size_type row_offset = 0;
            for (size_type i = 0; i < row; ++i) {
                row_offset += _offset[i];
            }
            // try to find the column-index in the _indices array for the correct row
            auto [index, exists_flag] = binary_search(
                _indices, row_offset, row_offset + _offset[row] - 1, col);
            return {row_offset, index, exists_flag};
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
            auto [row_offset, index, exists_flag] = search_for_element(row, col);

            if (exists_flag){
                _values[row_offset + index] += value;
            }
            else {
                auto it = _values.begin() + index;
                _values.insert(it, value);
                it = _indices.begin() + index;
                _indices.insert(it, col);
                _offset[row] += 1;
            }
        }

        // set element
        void set(size_type row, size_type col, value_type value) {
            auto [row_offset, index, exists_flag] = search_for_element(row, col);

            if (exists_flag){
                _values[row_offset + index] = value;
            }
            else {
                auto it = _values.begin() + index;
                _values.insert(it, value);
                it = _indices.begin() + index;
                _indices.insert(it, col);
                _offset[row] += 1;
            }
        }

        // compress storage
        void compress();

        // y := A * x
        void mv(std::vector<value_type> const& x, std::vector<value_type>& y);

        void print() {
            for (size_type i = 0; i < _nr; ++i)
            {
                for (size_type j = 0; j < _offset[i]; ++j)
                {
                    std::cout << '(' << i << ", " << _indices[j] << ") : " << _values[j] << "\n";
                }
            }
        }

    private:
        size_type _max_nz;
        size_type _nr;
        size_type _nc;
        std::vector<value_type> _indices;
        std::vector<value_type> _values;
        std::vector<value_type> _offset;
     
};
