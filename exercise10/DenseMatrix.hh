#pragma once

#include <cassert>
#include <utility>

#include "Vector.hh"

namespace scprog {

template <typename T>
class DenseMatrix {
public:
  // The data type of the matrix entries
  using value_type = T;

  // The data type of the size and indices
  using size_type = std::size_t;

public:
  // construct and initialize the matrix of size rows x cols
  DenseMatrix(size_type rows = 0, size_type cols = 0);

  DenseMatrix(size_type rows, size_type cols,
              std::initializer_list<value_type> l)
      : rows_(rows)
      , cols_(cols)
      , data_(l) {
    assert(l.size() == rows * cols);
  }

  // mutable access to the matrix entries
  value_type& operator()(size_type const i, size_type const j) {
    assert(i < rows_);
    assert(j < cols_);
    return data_[i * cols_ + j];
  }

  // const access to the matrix entries
  value_type const& operator()(size_type const i, size_type const j) const {
    assert(i < rows_);
    assert(j < cols_);
    return data_[i * cols_ + j];
  }

  // return the number of rows
  size_type rows() const { return rows_; }

  // return the number of columns
  size_type cols() const { return cols_; }

  // matrix-vector product y = A*x
  void mv(Vec<value_type> const& x, Vec<value_type>& y) const;

private:
  size_type   rows_;
  size_type   cols_;
  Vec<double> data_;
};

} // end namespace scprog
