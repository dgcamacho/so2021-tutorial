#pragma once

#include <algorithm>
#include <cassert>
#include <iterator>
#include <numeric>

#include "Vector.hh"

namespace scprog {

template <class T>
CRSMatrix<T>::CRSMatrix (size_type const rows, size_type const cols)
  : rows_(rows)
  , cols_(cols)
  , offset_(rows+1, 0u)
  , indices_(0u)
  , values_(0u)
{}


template <class T>
auto CRSMatrix<T>::exists (size_type const i, size_type const j) const -> bool
{
  // get index range of column indices
  auto begin_it = indices_.begin() + offset_[i];
  auto end_it = indices_.begin() + offset_[i+1];
  auto it = std::lower_bound(begin_it, end_it, j);
  return it != end_it && *it == j;
}


template <class T>
auto CRSMatrix<T>::operator() (size_type const i, size_type const j) const -> value_type
{
  auto begin_it = indices_.begin() + offset_[i];
  auto end_it = indices_.begin() + offset_[i+1];
  auto it = std::lower_bound(begin_it, end_it, j);
  size_type pos = std::distance(indices_.begin(), it);
  return it != end_it && *it == j ? values_[pos] : value_type(0);
}


template <class T>
auto CRSMatrix<T>::mv (Vector const& x, Vector& y) const
{
  assert(rows_ == y.size());
  assert(cols_ == x.size());
  for (size_type i = 0; i < rows_; ++i) {
    y[i] = value_type(0);

    for (size_type j = offset_[i]; j < offset_[i+1]; ++j)
      y[i] += values_[j] * x[indices_[j]];
  }
}


template <class T>
auto CRSMatrix<T>::inserter (size_type const slotsize) -> CRSMatrixInserter<T>
{
  return CRSMatrixInserter<T>{*this, slotsize};
}


template <class T>
CRSMatrixInserter<T>::CRSMatrixInserter (Matrix& matrix, size_type slotsize)
  : matrix_(matrix)
  , slotsize_(slotsize)
  , sizes_(matrix.rows_+1, 0u)
  , indices_(slotsize * matrix.rows_)
  , values_(slotsize * matrix.rows_)
{
  // copy the matrix data into the internal data structures to be filled up further
  if (matrix_.values_.size() > 0) {
    for (size_type i = 0; i < matrix_.rows_; ++i) {
      size_type offset = matrix_.offset_[i];
      sizes_[i] = matrix_.offset_[i+1] - offset;
      for (size_type j = 0; j < sizes_[i]; ++j) {
        indices_[i*slotsize_ + j] = matrix_.indices_[offset + j];
        values_[i*slotsize_ + j] = matrix_.values_[offset + j];
      }
    }
  }
}


template <class T>
  template <class Assign>
auto CRSMatrixInserter<T>::Updater::update (value_type const& value, Assign assign)
{
  assert(i_ < self_.matrix_.rows_);
  assert(j_ < self_.matrix_.cols_);

  auto begin_it = self_.indices_.begin() + i_*self_.slotsize_;
  auto end_it = begin_it + self_.sizes_[i_];
  auto it = std::lower_bound(begin_it, end_it, j_);
  assert(it != self_.indices_.end());

  size_type pos = std::distance(self_.indices_.begin(), it);

  if (it == end_it) {
    // no existing column index >= j --> insert a new element at the end
    *it = j_;
    self_.values_[pos] = value;
    self_.sizes_[i_]++;
  } else if (*it == j_) {
    // existing value at position (i,j) is updated
    assign(self_.values_[pos], value);
  } else {
    // other indices and values with column > j must be shifted
    size_type end_pos = std::distance(self_.indices_.begin(), end_it);
    for (size_type k = end_pos; k > pos; --k) {
      self_.indices_[k] = self_.indices_[k-1];
      self_.values_[k] = self_.values_[k-1];
    }
    self_.indices_[pos] = j_;
    self_.values_[pos] = value;
    self_.sizes_[i_]++;
  }
}


template <class T>
CRSMatrixInserter<T>::~CRSMatrixInserter ()
{
  size_type nnz = std::accumulate(sizes_.begin(), sizes_.end(),0);
  matrix_.indices_.resize(nnz);
  matrix_.values_.resize(nnz);

  size_type offset = 0;
  for (size_type i = 0; i < matrix_.rows_; ++i) {
    size_type colsize = sizes_[i];
    // copy the column indices ad values to its final position
    for (size_type j = 0; j < colsize; ++j) {
      matrix_.indices_[offset + j] = indices_[i*slotsize_ + j];
      matrix_.values_[offset + j] = values_[i*slotsize_ + j];
    }

    matrix_.offset_[i] = offset;
    offset += colsize;
  }
  matrix_.offset_.back() = offset;
  assert(offset == nnz);
}

} // end namespace scprog
