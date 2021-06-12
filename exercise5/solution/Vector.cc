#include "Vector.hh"

namespace scprog {

Vector::Vector (size_type const size)
  : data_(size, value_type(0))
{}


Vector& Vector::operator+=(Vector const& other)
{
  for (size_type i = 0; i < size(); ++i)
    data_[i] += other[i];
  return *this;
}


Vector& Vector::operator-=(Vector const& other)
{
  for (size_type i = 0; i < size(); ++i)
    data_[i] -= other[i];
  return *this;
}


Vector& Vector::operator*=(value_type const factor)
{
  for (size_type i = 0; i < size(); ++i)
    data_[i] *= factor;
  return *this;
}


Vector& Vector::operator/=(value_type const factor)
{
  for (size_type i = 0; i < size(); ++i)
    data_[i] /= factor;
  return *this;
}


Vector Vector::operator-()
{
  Vector result{*this};
  for (size_type i = 0; i < size(); ++i)
    result[i] = -data_[i];
  return result;
}


Vector operator+(Vector const& lhs, Vector const& rhs)
{
  Vector result{lhs};
  return result += rhs;
}


Vector operator-(Vector const& lhs, Vector const& rhs)
{
  Vector result{lhs};
  return result -= rhs;
}


Vector operator*(Vector::value_type factor, Vector const& vec)
{
  Vector result{vec};
  return result *= factor;
}


Vector operator*(Vector const& vec, Vector::value_type factor)
{
  Vector result{vec};
  return result *= factor;
}


Vector operator/(Vector const& vec, Vector::value_type factor)
{
  Vector result{vec};
  return result /= factor;
}


} // end namespace scprog
