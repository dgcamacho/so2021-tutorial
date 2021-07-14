#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <utility>

namespace scprog
{
  struct VectorOverloaded
  {
    std::size_t size_ = 0;
    double* data_ = nullptr;

    VectorOverloaded (std::size_t const size, double const value = 0.0)
      : size_(size)
      , data_(size > 0 ? new double[size] : nullptr)
    {
      std::fill(data_, data_+size_, value);
    }

    ~VectorOverloaded () { delete[] data_; }

    // copy constructor
    VectorOverloaded (VectorOverloaded const& other)
      : VectorOverloaded(other.size_)
    {
      std::copy(other.data_, other.data_+other.size_, this->data_);
    }

    // move constructor
    VectorOverloaded (VectorOverloaded&& other)
    {
      std::swap(size_, other.size_);
      std::swap(data_, other.data_);
    }

    // move/copy assignment operator
    VectorOverloaded& operator= (VectorOverloaded other)
    {
      std::swap(size_, other.size_);
      std::swap(data_, other.data_);
      return *this;
    }

    VectorOverloaded& operator+= (VectorOverloaded const& other)
    {
      assert(size_ == other.size());
      for (std::size_t i = 0; i < size_; ++i)
        data_[i] += other[i];
      return *this;
    }

    VectorOverloaded& operator-= (VectorOverloaded const& other)
    {
      assert(size_ == other.size());
      for (std::size_t i = 0; i < size_; ++i)
        data_[i] -= other[i];
      return *this;
    }


    double  operator[] (std::size_t i) const { return data_[i]; }
    double& operator[] (std::size_t i)       { return data_[i]; }

    std::size_t size () const { return size_; }
  };


  // binary + operator
  inline VectorOverloaded operator+ (VectorOverloaded const& lhs, VectorOverloaded const& rhs)
  {
    VectorOverloaded tmp(lhs);
    tmp += rhs;
    return tmp;
  }


} // end namespace scprog
