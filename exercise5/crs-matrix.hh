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
    using Value = T;
    using Size  = std::size_t;

    class CompressedMatrix {
    private:
      Size _rows;
      Size _cols;
      Vector<Size> _offsets;
      Vector<Size> _indices;
      Vector<Value> _values;
    public:
      // Build a compressed matrix from a sparse one by removing all
      // superfluous zeros.
      CompressedMatrix(CRSMatrix<T> const& mat);

      /**
       * Matrix-vector multiplication y = A · x.  The vectors x and y
       * must have matching size, such that we have rows() ≡ size(y) and
       * cols() ≡ size(x).
       */
      auto mv(Vector<Value> const& x, Vector<Value>& y) const -> void;
    };

  private:
    Size _rows;
    Size _cols;
    Size _max_non_zeros;    // max non zero elements in a single row
    Vector<Size> _offsets;
    Vector<Size> _indices;
    Vector<Value> _values;

    // Decide whether something already exists at the given index.
    struct NewElem { Size el; };
    struct OldElem { Size el; };
    using ElemWas = std::variant<NewElem, OldElem>;

    // Given some range within a vector, decide where to insert an
    // index.  /O(log n)/.
    auto find_ix(Vector<Size> const& vec, Size lo, Size hi, Size ix) -> ElemWas;

  public:
    /**
     * Construct a sparse matrix with the given rows and columns, as
     * well as the maximal number of non-zero elements _per row_.  This
     * number will be cut off at the column size if necessary.
     */
    explicit CRSMatrix(Size rows, Size cols, Size max_non_zeros);

    /**
     * Insert a non-zero value into the given coordinates (i, j).  The
     * coordinates must be valid; if the value already exists then
     * modify it with an arbitrary function.  The function takes the
     * arguments `(old_value, value)`.
     */
    template <std::invocable<Value, Value> Op>
    auto modify(Op change_el, Size i, Size j, Value value) -> void;

    // Like `modify`, but add the given value onto the existing one if
    // necessary.
    auto add(Size i, Size j, Value value) -> void;

    // Like `modify`, but replace the existing value if necessary.
    auto set(Size i, Size j, Value value) -> void;

    // Compress a sparse matrix into its "final" form.  Namely, a
    // representation without redundant zeros.
    auto compress() -> CompressedMatrix;

  };
}

#include "crs-matrix.impl.hh"
