#include "DenseMatrix.hh"
#include "LU.hh"
#include "Vector.hh"

#include <cassert>

namespace scprog {

  auto LU::compute(DenseMatrix const& m) -> void {
    assert(m.rows() == m.cols());
    Size n {m.rows()};
    _decomposition = m;
    for (Size i = 0; i < n - 1; ++i) {
      for (Size k = i + 1; k < n; ++k) {
        (*this)(k, i) /= (*this)(i, i);
        for (Size j = i + 1; j < n; ++j) {
          (*this)(k, j) -= (*this)(k, i) * (*this)(i, j);
        }
      }
    }
  }

  auto LU::apply(Vector const& b, Vector& x) const -> void {
    // Consistency assumption: cols ≡ rows by construction.
    Size n {_decomposition.rows()};
    assert(n == b.size() && n == x.size());

    // Solve L · y = b
    x = b;                            // No extra vector y needed
    for (Size i = 1; i < n; ++i) {
      for (Size k = 0; k < i; ++k) {
        x[i] -= (*this)(i, k) * x[k];
      }
    }

    // Solve R · x = y
    for (Size i = n; i > 0; --i) {
      for (Size k = i; k < n; ++k) {
        x[i - 1] -= (*this)(i - 1, k) * x[k];
      }
      x[i - 1] /= (*this)(i - 1, i - 1);
    }
  }

}
