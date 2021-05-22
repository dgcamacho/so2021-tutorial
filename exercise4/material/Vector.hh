#pragma once

#include "Util.hh"

#include <vector>

namespace scprog {

  class Vector {
  public:
    // Construct and initialize a vector of the given size.
    Vector(Size size);

    // Construct a vector from a given initializer list.
    Vector(InitializerList<Value>);

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

  // Pretty print a vector of length n as "[x₁, ..., xₙ]".
  auto operator<<(OStream& os, Vector const& vec) -> OStream&;

  // Subtract two vectors from each other element-wise.  The vectors
  // need to have the same length.
  auto operator-(Vector const& l, Vector const& r) -> Vector;

} // end namespace scprog
