#include "DenseMatrix.hh"
#include "Util.hh"
#include "Vector.hh"

#include <cassert>

namespace scprog {

  DenseMatrix::DenseMatrix(Size const rows, Size const cols)
      : _rows(rows), _cols(cols), _data(_rows * _cols, 0) {}

  DenseMatrix::DenseMatrix(Size const rows, Size const cols, InitializerList<Value> init)
      : _rows(rows), _cols(cols), _data(init) {
    assert (init.size() == cols * rows);
  }

  auto DenseMatrix::operator()(Size const i, Size const j) -> Value& {
    assert(i * j < _rows * _cols);
    return _data[i * _cols + j];
  }

  auto DenseMatrix::operator()(Size const i, Size const j) const -> Value const& {
    assert(i * j < _rows * _cols);
    return _data[i * _cols + j];
  }

  auto DenseMatrix::rows() const -> Size {
    return _rows;
  }

  auto DenseMatrix::cols() const -> Size {
    return _cols;
  }

  auto DenseMatrix::mv(Vector const& x, Vector& y) const -> void {
    assert(_rows == _cols && x.size() == _rows && y.size() == _rows);
    for (Size i = 0; i < _rows; ++i) {
      y[i] = 0;  // we don't know what the vector looks like, so be sure
      for (Size j = 0; j < _cols; ++j) {
        y[i] += (*this)(i, j) * x[j];
      }
    }
  }

} // end namespace scprog
