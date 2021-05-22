#include <iostream>
#include "Vector.hh"

namespace scprog {

Vector::Vector (size_type const size)
{
  // copy-assignment
  data_ = std::vector<value_type>(size, 0); 
}


Vector::value_type& Vector::operator[] (size_type const i)
{
  return data_[i];
}


Vector::value_type const& Vector::operator[] (size_type const i) const
{
  return data_[i];
}


Vector::size_type Vector::size () const
{
  return data_.size();
}

Vector Vector::operator- (Vector v) {
  Vector difference = (*this);
  if ((*this).size() == (v.size())) {
    for (int i = 0; i < v.size(); ++i) {
      difference[i] -= v[i];
    }
  }
  return difference;
}

void Vector::print() {
  std::cout << "(";
  for (int i = 0; i < (*this).size() - 1; ++i) {
    std::cout << (*this)[i] << ", ";
  }
  std::cout << (*this)[(*this).size() - 1] << ")" << std::endl;

}
} // end namespace scprog
