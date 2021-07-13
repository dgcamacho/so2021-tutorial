#pragma once

#include <algorithm>
#include <cassert>
#include <functional>
#include <variant>
#include <vector>

namespace scprog {

template <typename T>
using Vector = std::vector<T>;

template <typename T>
class CRSMatrix {
public:
  using value_type = T;
  using size_type  = std::size_t;

  class CompressedMatrix {
  private:
    size_type          _rows;
    size_type          _cols;
    Vector<size_type>  _offsets;
    Vector<size_type>  _indices;
    Vector<value_type> _values;

  public:
    // Build a compressed matrix from a sparse one by removing all
    // superfluous zeros.
    CompressedMatrix(CRSMatrix<T> const& mat);

    /**
     * Matrix-vector multiplication y = A · x.  The vectors x and y
     * must have matching size, such that we have rows() ≡ size(y) and
     * cols() ≡ size(x).
     */
    auto mv(Vector<value_type> const& x, Vector<value_type>& y) const -> void;
  };

private:
  size_type          _rows;
  size_type          _cols;
  size_type          _max_non_zeros; // max non zero elements in a single row
  Vector<size_type>  _offsets;
  Vector<size_type>  _indices;
  Vector<value_type> _values;

  // Decide whether something already exists at the given index.
  struct NewElem {
    size_type el;
  };
  struct OldElem {
    size_type el;
  };
  using ElemWas = std::variant<NewElem, OldElem>;

  // Given some range within a vector, decide where to insert an
  // index.  /O(log n)/.
  auto find_ix(Vector<size_type> const& vec, size_type lo, size_type hi,
               size_type ix) -> ElemWas;

public:
  /**
   * Construct a sparse matrix with the given rows and columns, as
   * well as the maximal number of non-zero elements _per row_.  This
   * number will be cut off at the column size if necessary.
   */
  explicit CRSMatrix(size_type rows, size_type cols, size_type max_non_zeros);

  /**
   * Insert a non-zero value into the given coordinates (i, j).  The
   * coordinates must be valid; if the value already exists then
   * modify it with an arbitrary function.  The function takes the
   * arguments `(old_value, value)`.
   */
  template <std::invocable<value_type, value_type> Op>
  auto modify(Op change_el, size_type i, size_type j, value_type value) -> void;

  // Like `modify`, but add the given value onto the existing one if
  // necessary.
  auto add(size_type i, size_type j, value_type value) -> void;

  // Like `modify`, but replace the existing value if necessary.
  auto set(size_type i, size_type j, value_type value) -> void;

  // Compress a sparse matrix into its "final" form.  Namely, a
  // representation without redundant zeros.
  auto compress() -> CompressedMatrix;
};

} // namespace scprog

#include "CRSMatrix.impl.hh"
