#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <utility>

namespace scprog
{
  template <class E>
  struct Expr
  {
    // Element access
    auto operator[] (std::size_t const i) const
    {
      return static_cast<E const&>(*this).access_impl(i);
    }

    auto& operator[] (std::size_t const i)
    {
      return static_cast<E&>(*this).access_impl(i);
    }

    // Length of the vector expression
    auto size () const
    {
      return static_cast<E const&>(*this).size_impl();
    }

  protected:
    Expr () = default;
  };

  template <class Functor, class A, class B>
  class BinaryExpr : public Expr< BinaryExpr<Functor,A,B> >
  {
    Functor f_;
    A const& a_;
    B const& b_;

  public:
    BinaryExpr (Functor f, A const& a, B const& b)
      : f_(f), a_(a), b_(b)
    {
      assert(a_.size() == b_.size());
    }

    // implementation of element access
    double access_impl (std::size_t i) const { return f_( a_[i], b_[i] ); }

    // implementation of size information
    auto size_impl () const { return a_.size(); }
  };

  template <class Functor, class A>
  class UnaryExpr : public Expr< UnaryExpr<Functor,A> >
  {
    Functor f_;
    A const& a_;

  public:
    UnaryExpr (Functor f, A const& a)
      : f_(f), a_(a)
    {}

    // implementation of element access
    double access_impl (std::size_t i) const { return f_( a_[i] ); }

    // implementation of size information
    auto size_impl () const { return a_.size(); }
  };

} // end namespace scprog
