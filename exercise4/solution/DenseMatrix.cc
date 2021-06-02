#include "DenseMatrix.hh"
#include "Vector.hh"

namespace scprog {

DenseMatrix::DenseMatrix (size_type const rows, size_type const cols)
  : rows_(rows)
  , cols_(cols)
  , data_(rows*cols, value_type(0))
{}


void DenseMatrix::mv (Vector const& x, Vector& y) const
{
  assert(rows_ == y.size());
  assert(cols_ == x.size());
  for (std::size_t i = 0; i < rows_; ++i)
  {
    value_type f = 0;
    for (std::size_t j = 0; j < cols_; ++j)
      f += data_[i*cols_ + j] * x[j];
    y[i] = f;
  }
}

} // end namespace scprog
