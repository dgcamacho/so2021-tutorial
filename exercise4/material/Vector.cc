#include "Util.hh"
#include "Vector.hh"

#include <cassert>

namespace scprog {

  Vector::Vector(Size const size) : _data(size, 0.0) {}

  auto Vector::operator[](Size const i) -> Value& {
    assert(i < _data.size());
    return _data[i];
  }

  auto Vector::operator[](Size const i) const -> Value const& {
    assert(i < _data.size());
    return _data[i];
  }

  auto Vector::size() const -> Size {
    return _data.size();
  }
} // end namespace scprog
