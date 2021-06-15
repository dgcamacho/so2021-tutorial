#pragma once

#include <cstddef> // std::size_t

class CGSolver
{
public:
  CGSolver (std::size_t const maxIt, double const eps)
    : maxIt_(maxIt)
    , eps_(eps)
  {}

  // solve the linear system A*x = b, return the result x
  template <typename Mat, typename Vec>
  Vec solve (Mat const& A, Vec const& b) const
  {
    Vec x(y.size());
    x = 0.0;

    Vec r = y - A * x;
    Vec p = r;

    for (std::size_t i = 0; i < maxIt_; ++i)
    {
      auto const alpha = r.dot(r) / p.dot(A * p);
      x = x + alpha * p;
      auto const r_new = r - alpha * (A * p);
      if (r_new.two_norm() < eps_)
        break;
      else{
        auto const beta = r_new.dot(r_new) / r.dot(r);
        p = r_new + beta * p;
        r = r_new;
      }
    }
    return x;
  }

private:
  std::size_t maxIt_;
  double eps_;
};
