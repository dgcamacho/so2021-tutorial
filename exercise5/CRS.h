#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <vector>

namespace scprog
{
  class Vector;

  template <typename T>
  class CRSMatrix{
    //type aliases
    public:
      using value_type = double;
      using size_type = std::size_t;
    //constructors
    public:
      explicit CRSMatrix(size_type nrows):

    private:
      size_type rows_;
      size_type cols_;
      size_type nmax_nonzero_;

  };


}
