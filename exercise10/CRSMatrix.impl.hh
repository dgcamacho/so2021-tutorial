#pragma once

namespace scprog {

/*
 * Take in a bunch of lambdas and expose their `()` operator.  This is
 * very useful when doing pseudo pattern-matching on arbitrary sum
 * types.
 *
 * Source: https://en.cppreference.com/w/cpp/utility/variant/visit
 */
template <typename... Ts>
struct overloaded : Ts... {
  using Ts::operator()...;
};
template <typename... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

template <typename T>
CRSMatrix<T>::CRSMatrix(size_type const rows, size_type const cols,
                        size_type const max_non_zeros)
    : _rows{rows}
    , _cols{cols}
    , _max_non_zeros{std::min(cols, max_non_zeros)}
    , _offsets(rows + 1, 0) // extra row for zero in first pos
    , _indices(std::min(cols, max_non_zeros) * rows, 0)
    , _values(std::min(cols, max_non_zeros) * rows, 0) {}

template <typename T>
auto CRSMatrix<T>::find_ix(Vector<size_type> const& vec, size_type const lo,
                           size_type const hi, size_type const ix) -> ElemWas {
  assert(lo <= hi);
  if (ix < vec[lo]) return NewElem{lo};
  if (ix > vec[hi]) return NewElem{hi + 1};
  size_type const mid = (lo + hi) / 2;
  if (vec[mid] == ix) return OldElem{mid};
  if (vec[mid] < ix && vec[mid + 1] > ix) return NewElem{mid + 1};
  // Yay, recursion!
  if (vec[mid] > ix) return find_ix(vec, lo, mid - 1, ix);
  if (vec[mid] < ix) return find_ix(vec, mid + 1, hi, ix);
  return OldElem{0}; // Impossible, but the compiler doesn't believe me :(
}

// This can't be merged into one because it really is a template
// function within a template class...
template <typename T>
template <std::invocable<T, T> Op>
auto CRSMatrix<T>::modify(Op modify_value, size_type const i, size_type const j,
                          value_type const value) -> void {
  assert(i < _rows && j < _cols); // index in range
  assert(value != 0);             // non-zero value
  size_type const elems =         // non-zero elems stored within the row
      (_offsets[i + 1] < _offsets[i]) ? 0 : _offsets[i + 1] - _offsets[i];
  assert(elems < _max_non_zeros); // enough space for another one

  size_type const lo = i * _max_non_zeros;
  size_type const hi = (elems == 0) ? lo : lo - 1 + elems;
  ElemWas const   ix = (elems == 0) ? NewElem{_max_non_zeros * i}
                                  // first non-zero element
                                    : find_ix(_indices, lo, hi, j);

  // No pattern matching in C++ :( This is better than an if
  // statement, but still pretty limited.
  std::visit(overloaded{
                 [this, &hi, &value, &i, &j](NewElem const& fresh) {
                   size_type el = fresh.el;
                   // If necessary, move elements out of the way.
                   if (_values[el] != 0) {
                     for (size_type k = hi; k != el - 1; --k) {
                       _values[k + 1]  = _values[k];
                       _indices[k + 1] = _indices[k];
                     }
                   }
                   // Update vectors.
                   _indices[el] = j;
                   _values[el]  = value;
                   std::for_each(_offsets.begin() + i + 1, _offsets.end(),
                                 [](size_type& el) { ++el; });
                 },
                 [this, &modify_value, &value](OldElem const& old) {
                   size_type el = old.el;
                   _values[el]  = modify_value(_values[el], value);
                 },
             },
             ix);
}

template <typename T>
auto CRSMatrix<T>::set(size_type const i, size_type const j,
                       value_type const value) -> void {
  modify([](size_type, size_type new_v) { return new_v; }, i, j, value);
}

template <typename T>
auto CRSMatrix<T>::add(size_type const i, size_type const j,
                       value_type const value) -> void {
  modify(std::plus<size_type>(), i, j, value);
}

template <typename T>
auto CRSMatrix<T>::compress() -> CompressedMatrix {
  return CompressedMatrix(*this);
}

template <typename T>
CRSMatrix<T>::CompressedMatrix::CompressedMatrix(CRSMatrix<T> const& mat) {
  Vector<size_type> indices;
  indices.reserve(mat._offsets[mat._rows]);
  Vector<value_type> values;
  values.reserve(mat._offsets[mat._rows]);

  _offsets = mat._offsets;
  _rows    = mat._rows;
  _cols    = mat._cols;
  for (size_type i = _rows; i > 0; --i) {
    size_type const elems = _offsets[i] - _offsets[i - 1];
    size_type const start = (i - 1) * mat._max_non_zeros;
    size_type const stop  = start + elems;
    indices.insert(indices.begin(), mat._indices.begin() + start,
                   mat._indices.begin() + stop);
    values.insert(values.begin(), mat._values.begin() + start,
                  mat._values.begin() + stop);
  }
  _indices = indices;
  _values  = values;
}

template <typename T>
auto CRSMatrix<T>::CompressedMatrix::mv(Vector<value_type> const& x,
                                        Vector<value_type>& y) const -> void {
  for (size_type i = 0; i < _rows; ++i) {
    value_type f     = 0;
    auto const start = _offsets[i];
    auto const stop  = _offsets[i + 1];
    for (size_type j = start; j < stop; ++j) {
      f += _values[j] * x[_indices[j]];
    }
    y[i] += f;
  }
}

} // namespace scprog
