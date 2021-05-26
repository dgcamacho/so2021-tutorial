#pragma once

#include <vector>

namespace scprog
{
  // forward declaration
  class Vector;

  class DenseMatrix
  {
  public:
  	// The data type of the matrix entries
  	using value_type = double;

    // The data type of the size and indices
    using size_type = std::size_t;

  public:
    // construct and initialize the matrix of size rows x cols
    DenseMatrix (size_type rows, size_type cols);

		// copy constructor
		DenseMatrix (DenseMatrix const& m);

    // mutable access to the matrix entries
    value_type& operator() (size_type i, size_type j);

    // const access to the matrix entries
    value_type const& operator() (size_type i, size_type j) const;

    // return the number of rows
    size_type rows () const;

    // return the number of columns
    size_type cols () const;

    // matrix-vector product y = A*x
    void mv (Vector const& x, Vector& y) const;

		DenseMatrix& operator*= (DenseMatrix const& other)
		{
			std::vector<value_type> tmp (rows_ * other.cols_, 0.0);
			for (size_type i{0}; i < rows_; ++i) {
				for (size_type j{0}; j < other.cols_; ++j) {
					for (size_type k{0}; k < cols_; ++k) {
						tmp[i* other.cols_ + j] += data_[i*cols_ + k] * other.data_[k*other.cols_ + j];
					}
				}
			}
			data_ = tmp;
			return *this;
		}

		DenseMatrix& operator-= (DenseMatrix const& other)
		{
			for (size_type i{0}; i < rows_; ++i) {
				for (size_type j{0}; j < cols_; ++j) {
					data_[i*cols_ + j] -= other.data_[i*cols_ + j];
				}
			}
			return *this;
		}

    DenseMatrix& operator= (DenseMatrix const& that)
		{
			if (this != &that) {          // prevent from self assignment
				data_.clear();             // delete the old data first
				data_.shrink_to_fit();
				rows_ = that.rows_;
				cols_ = that.cols_;
				data_ = std::vector<value_type>(rows_ * cols_, 0.0);  // allocate new data
				// copy the data
				for (size_type i{0}; i < rows_; ++i) {
					for (size_type j{0}; j < cols_; ++j) {
						data_[i*cols_ + j] = that(i, j);
					}
				}
			}
			return *this;
		}

		// scales the matrix by a factor, changes the matrix
		void scale (double factor);

  private:
    size_type rows_;
    size_type cols_;
    std::vector<value_type> data_;
  };

	// product of two vectors resulting in a matrix
	DenseMatrix prod (Vector const& vec1, Vector const& vec2);

} // end namespace scprog

scprog::DenseMatrix operator* (scprog::DenseMatrix const& lhs, scprog::DenseMatrix const& rhs);

scprog::DenseMatrix operator- (scprog::DenseMatrix const& lhs, scprog::DenseMatrix const& rhs);
