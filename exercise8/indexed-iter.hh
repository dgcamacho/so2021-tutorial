#pragma once

#include "common.hh"

#include <utility>

namespace lagrange {

template <typename Iter, typename Index = Size> class IndexedIter {
private:
  Iter _iter;
  Index _ix;

public:
  using IndexedElem = decltype(std::pair{*_iter, _ix});

  explicit IndexedIter(Iter it, Index ix = 0) : _iter(it), _ix(ix) {}

  auto operator++() -> IndexedIter& {
    ++_iter;
    ++_ix;
    return *this;
  }

  auto operator++(int) -> IndexedIter {
    auto tmp(*this);
    ++(*this);
    return tmp;
  }

  auto operator*() const -> IndexedElem { return std::pair{*_iter, _ix}; }

  auto operator==(IndexedIter const& other) const -> bool {
    return _iter == other._iter;
  }
};

} // namespace lagrange
