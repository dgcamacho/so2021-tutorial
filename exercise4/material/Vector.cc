#include "Vector.hh"

namespace scprog {

Vector::Vector (size_type const size)
{
  this->data_ = std::vector<value_type>(size, 0.0);
}

Vector::Vector (Vector const& v)
{
	data_ = std::vector<value_type>(v.size(), 0.0);
	for (size_type i{0}; i < v.size(); ++i) {
		data_[i] = v.data_[i];
	}
}

Vector::value_type& Vector::operator[] (size_type const i)
{
  return this->data_[i];
}


Vector::value_type const& Vector::operator[] (size_type const i) const
{
  return this->data_[i];
}


Vector::size_type Vector::size () const
{
  return this->data_.size();
}

void Vector::scale (double const factor)
{
	for (size_type i{0}; i < data_.size(); ++i) {
		data_[i] *= factor;
	}
}

} // end namespace scprog

scprog::Vector operator- (scprog::Vector const& lhs, scprog::Vector const& rhs)
{
	scprog::Vector tmp{lhs};
	return tmp -= rhs;
}