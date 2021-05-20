#pragma once

#include "Util.hh"

#include <vector>

namespace scprog {

  class Vector {
  public:
    // Construct and initialize a vector of the given size.
    Vector(Size size);

    // Mutable access to the vector entry.  The index must be valid for
    // the given vector.
    auto operator[](Size i) -> Value&;

    // Const access to the vector entry.  The index must be valid for
    // the given vector.
    auto operator[](Size i) const -> Value const&;

    // Return the size of the vector.
    auto size() const -> Size;

  private:
    std::vector<Value> _data;
  };

} // end namespace scprog
