#include "Vector.hh"

namespace scprog {

Vector::Vector (size_type const size)
{
	data_ = std::vector<value_type>(size, 0.0);
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
	return data_[i];
}

Vector::value_type const& Vector::operator[] (size_type const i) const
{
	return data_[i];
}

Vector& Vector::operator= (Vector const& that)
{
	if (this != &that) {          // prevent from self assignment
		data_.clear();             // delete the old data first
		data_.shrink_to_fit();
		data_ = std::vector<value_type>(that.size(), 0.0);  // allocate new data
		for (size_type i = 0; i < that.size(); ++i)  // copy the data
			data_[i] = that.data_[i];
	}
	return *this;
}

Vector& Vector::operator-= (Vector const& other)
{
	for (size_type i{0}; i < other.size(); ++i) {
		data_[i] -= other.data_[i];
	}
	return *this;
}

Vector::size_type Vector::size () const
{
	return data_.size();
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