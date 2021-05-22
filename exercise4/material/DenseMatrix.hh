#pragma once

#include "Util.hh"

#include <vector>

namespace scprog {

  // forward declaration
  class Vector;

  class DenseMatrix {
  public:
    // Construct and initialize the matrix of size rows x cols.
    DenseMatrix(Size rows, Size cols);

    // Construct a matrix of size rows × cols and initialize it with the
    // given list.  The list has to be of length rows × cols.
    DenseMatrix(Size rows, Size cols, InitializerList<Value> init);

    // Mutable access to the matrix entries.  The tuple (i, j) must be a
    // valid entry in the matrix.
    auto operator()(Size i, Size j) -> Value&;

    // Const access to the matrix entries.  The tuple (i, j) must be a
    // valid entry in the matrix.
    auto operator()(Size i, Size j) const -> Value const&;

    // Return the number of rows.
    auto rows() const -> Size;

    // Return the number of columns.
    auto cols() const -> Size;

    // Matrix-vector product y = A · x.  The given Matrix A must be of
    // size n × n, for n ≔ size(y) ≡ size(x).
    auto mv(Vector const& x, Vector& y) const -> void;

  private:
    Size _rows;
    Size _cols;
    std::vector<Value> _data;
  };

} // end namespace scprog
