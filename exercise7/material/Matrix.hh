#pragma once

#include <cassert>

#include "Vector.hh"

class Matrix
{
  std::size_t rows_;
  std::size_t cols_;
  std::vector<double> data_;

public:
  Matrix () = default;

  Matrix (std::vector<std::vector<double>> const& entries)
    : rows_(entries.size())
    , cols_(entries.empty() ? 0u : entries[0].size())
    , data_(rows_ * cols_)
  {
    // check that all rows have the same length
    for (auto const& row : entries)
      assert(row.size() == cols_);

    // copy all entries into the internal data structure
    for (std::size_t i = 0; i < rows_; ++i)
      for (std::size_t j = 0; j < cols_; ++j)
        (*this)(i, j) = entries[i][j];
  }

  Matrix (std::size_t const rows, std::size_t const cols)
    : rows_(rows)
    , cols_(cols)
    , data_(rows * cols)
  {}

  // mutable access to the (i,j)th element
  double& operator() (std::size_t const i, std::size_t const j)
  {
    return data_[i * rows_ + j];
  }

  // const access to the (i,j)th element
  double const& operator() (std::size_t const i, std::size_t const j) const
  {
    return data_[i * rows_ + j];
  }

  // set all entries to `value`
  Matrix& operator= (double const value)
  {
    data_.assign(data_.size(), value);
    return *this;
  }

  // number of rows
  std::size_t rows () const
  {
    return rows_;
  }

  // number of columns
  std::size_t cols () const
  {
    return cols_;
  }

  // Matrix * Vector product y = A * x
  void mv (Vector const& x, Vector& y) const
  {
    assert(x.size() == cols());
    assert(y.size() == rows());
    for (std::size_t i = 0; i < rows(); ++i) {
      y(i) = 0.0;
      for (std::size_t j = 0; j < cols(); ++j) {
        y(i) += (*this)(i,j)*x(j);
      }
    }
  }

  // Matrix * Vector product A * x
  Vector operator* (Vector const& x) const
  {
    assert(x.size() == cols());
    Vector y(rows());
    y = 0.0;
    this->mv(x, y);
    return y;
  }
};
