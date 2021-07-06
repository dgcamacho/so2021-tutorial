#pragma once

#include <algorithm>
#include <cassert>
#include <iterator>
#include <numeric>
#include <tuple>

#include "Vector.hh"

namespace scprog {

template <class T>
CRSMatrix<T>::CRSMatrix (size_type const rows, size_type const cols, size_type const slotsize)
  : rows_(rows)
  , cols_(cols)
  , slotsize_(slotsize)
  , offset_(rows+1, 0u)
  , indices_(slotsize * rows)
  , values_(slotsize * rows)
{}

template <class T>
  template <class Assign>
auto CRSMatrix<T>::insert (size_type const i, size_type const j, value_type const& value,
                           Assign assign) -> void
{
  assert(!compressed_);
  assert(i < rows_);
  assert(j < cols_);

  auto begin_it = indices_.begin() + i*slotsize_;
  auto end_it = begin_it + offset_[i];
  auto it = std::lower_bound(begin_it, end_it, j);
  assert(it != indices_.end());

  size_type pos = std::distance(indices_.begin(), it);

  if (it == end_it) {
    // no existing column index >= j --> insert a new element at the end
    *it = j;
    values_[pos] = value;
    offset_[i]++;
  } else if (*it == j) {
    // existing value at position (i,j) is updated
    assign(values_[pos], value);
  } else {
    // other indices and values with column > j must be shifted
    size_type end_pos = std::distance(indices_.begin(), end_it);
    for (size_type k = end_pos; k > pos; --k) {
      indices_[k] = indices_[k-1];
      values_[k] = values_[k-1];
    }
    indices_[pos] = j;
    values_[pos] = value;
    offset_[i]++;
  }
}


template <class T>
auto CRSMatrix<T>::compress () -> void
{
  size_type nnz = std::accumulate(offset_.begin(), offset_.end(),0);

  size_type offset = 0;
  for (size_type i = 0; i < rows_; ++i) {
    size_type colsize = offset_[i];
    if (offset < i*slotsize_) {
      // copy the column indices ad values to its final position
      for (size_type j = 0; j < colsize; ++j) {
        indices_[offset + j] = indices_[i*slotsize_ + j];
        values_[offset + j] = values_[i*slotsize_ + j];
      }
    }

    offset_[i] = offset;
    offset += colsize;
  }
  offset_.back() = offset;
  assert(offset == nnz);

  indices_.resize(nnz);
  values_.resize(nnz);

  compressed_ = true;
}


template <class T>
auto CRSMatrix<T>::exists (size_type const i, size_type const j) const -> bool
{
  // get index range of column indices
  auto [begin_it, end_it] = [&]{
    if (compressed_)
      return std::pair{indices_.begin() + offset_[i], indices_.begin() + offset_[i+1]};
    else
      return std::pair{indices_.begin() + i*slotsize_, indices_.begin() + i*slotsize_ + offset_[i]};
  }();

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
auto CRSMatrix<T>::mv (Vector const& x, Vector& y) const -> void
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
auto CRSMatrix<T>::nnz () const -> size_type
{
  assert(compressed_);
  return values_.size();
}

} // end namespace scprog
