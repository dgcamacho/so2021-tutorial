#pragma once

#include <vector>

namespace scprog
{
  class Vector
  {
  public:
    // The data type of the matrix entries
    using value_type = double;

    // The data type of the size and indices
    using size_type = std::size_t;

  public:
    // construct and initialize the matrix of size rows x cols
    Vector (size_type size);

    // copy constructor
    Vector (Vector const& v);

    // mutable access to the matrix entries
    value_type& operator[] (size_type i);

    // const access to the matrix entries
    value_type const& operator[] (size_type i) const;

    // return the number of vector entries
    size_type size () const;

		Vector& operator= (Vector const& that)
		{
			if (this != &that) {          // prevent from self assignment
				data_.clear();             // delete the old data first
				data_.shrink_to_fit();
				data_ = std::vector<value_type>(that.size(), 0.0);  // allocate new data
				// copy the data
				for (size_type i = 0; i < that.size(); ++i)
					data_[i] = that.data_[i];
			}
			return *this;
		}

    Vector& operator-= (Vector const& other)
		{
			for (size_type i{0}; i < other.size(); ++i) {
				data_[i] -= other.data_[i];
			}
			return *this;
		}

    // scales the vector by a factor, changes the vector
		void scale (double const factor);

  private:
    std::vector<value_type> data_;
  };

} // end namespace scprog

scprog::Vector operator- (scprog::Vector const& lhs, scprog::Vector const& rhs);

