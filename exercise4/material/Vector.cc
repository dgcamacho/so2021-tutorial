#include "Util.hh"
#include "Vector.hh"

#include <cassert>

namespace scprog {

  Vector::Vector(Size const size) : _data(size, 0.0) {}

  Vector::Vector(InitializerList<Value> init) : _data(init) {}

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

  auto operator<<(OStream& os, Vector const& vec) -> OStream& {
    os << "[";
    for (Size i = 0; i < vec.size() - 1; ++i) {
      os << vec[i] << ", ";
    }
    os << vec[vec.size() - 1] << "]";
    return os;
  }

  auto operator-(Vector const& l, Vector const& r) -> Vector {
    assert(l.size() == r.size());
    Vector res(l.size());
    for (Size i = 0; i < l.size(); ++i) {
      res[i] = l[i] - r[i];
    }
    return res;
  }

} // end namespace scprog
