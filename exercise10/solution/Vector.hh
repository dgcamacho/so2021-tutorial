#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <utility>

#include "Expr.hh"

namespace scprog
{

  struct Vector : public Expr<Vector>
  {
    std::size_t size_ = 0;
    double* data_ = nullptr;

    Vector (std::size_t const size, double const value = 0.0)
      : size_(size)
      , data_(size > 0 ? new double[size] : nullptr)
    {
      std::fill(data_, data_+size_, value);
    }

    ~Vector () { delete[] data_; }

    Vector (Vector const& other)
      : Vector(other.size_)
    {
      std::copy(other.data_, other.data_+other.size_, this->data_);
    }

    template <class E>
    Vector (Expr<E> const& expr)  // construction from expression
      : Vector(expr.size())
    {
      for (std::size_t i = 0; i < size_; ++i)       // Evaluate the expression elementwise
        data_[i] = expr[i];
    }

    Vector& operator= (Vector other)
    {
      std::swap(size_, other.size_);
      std::swap(data_, other.data_);
      return *this;
    }

    template <class E>
    Vector& operator= (Expr<E> const& expr)
    {
      assert(size_ == expr.size());
      for (std::size_t i = 0; i < size_; ++i)       // Evaluate the expression elementwise
        data_[i] = expr[i];
      return *this;
    }

    template <class E>
    Vector& operator+= (Expr<E> const& expr)
    {
      assert(size_ == expr.size());
      for (std::size_t i = 0; i < size_; ++i)       // Evaluate the expression elementwise
        data_[i] += expr[i];
      return *this;
    }

    double  access_impl (std::size_t i) const { return data_[i]; }
    double& access_impl (std::size_t i)       { return data_[i]; }

    std::size_t size_impl () const { return size_; }
  };

} // end namespace scprog
