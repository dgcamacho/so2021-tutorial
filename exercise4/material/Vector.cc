#include "Vector.hh"

#include <iostream>
#include <vector>

namespace scprog {
	
Vector::Vector (size_type const size) 
	: data_(size, 0.0) 
	{}

Vector::value_type& Vector::operator[] (size_type const i)
{
  return data_[i];
}

// read only objects (const after the function name)
// returns const data (const&)
// we do not modify the data => you are allowed to call this function on a const object
Vector::value_type const& Vector::operator[] (size_type const i) const
{
  return data_[i];
}

void Vector::setValue (size_type const position, value_type const value)
{
  data_[position] = value;
}

// initializes a Vector with all given Values
void Vector::initialize (std::vector<value_type> const& allValues)
{
  if (data_.size() == allValues.size())	
  {
    data_ = allValues;
  } else {
	std::cout << "Could not initialize vector due to size incompatibility" << std::endl;
  }	
}

// implements the minus (-) operator
// calculates x=x-y where x is the Vector this operator is called on
Vector& Vector::operator- (Vector const& y)
{
  for (Vector::size_type i=0; i<size(); ++i) 
  {
	data_[i] -= y[i];  
  }	
  return *this;
}


Vector::size_type Vector::size () const
{
  return data_.size(); 
}

} // end namespace scprog
