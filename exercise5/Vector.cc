#include "Vector.hh"

namespace scprog {

Vector::Vector (size_type const size)
  : data_(size, value_type(0))
{}

} // end namespace scprog
