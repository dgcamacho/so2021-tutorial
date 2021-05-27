#include "DenseMatrix.hh"
#include "Vector.hh"

#include <cassert>
namespace scprog {

DenseMatrix::DenseMatrix (size_type const rows, size_type const cols)
{
	rows_ = rows;
	cols_ = cols;
	data_ = std::vector<value_type>(rows_ * cols_, 0.0);
}

DenseMatrix::DenseMatrix (DenseMatrix const& m)
{
	rows_ = m.rows_;
	cols_ = m.cols_;
	data_ = std::vector<value_type>(rows_ * cols_, 0.0);
	for (size_type i{0}; i < rows_; ++i) {
		for (size_type j{0}; j < cols_; ++j) {
			data_[i*cols_ + j] = m.data_[i*cols_ + j];
		}
	}
}

DenseMatrix::value_type& DenseMatrix::operator() (size_type const i, size_type const j)
{
	return data_[i * cols_ + j];
}

DenseMatrix::value_type const& DenseMatrix::operator() (size_type const i, size_type const j) const
{
	return data_[i * cols_ + j];
}

DenseMatrix& DenseMatrix::operator*= (DenseMatrix const& other)
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

DenseMatrix& DenseMatrix::operator-= (DenseMatrix const& other)
{
	for (size_type i{0}; i < rows_; ++i) {
		for (size_type j{0}; j < cols_; ++j) {
			data_[i*cols_ + j] -= other.data_[i*cols_ + j];
		}
	}
	return *this;
}

DenseMatrix& DenseMatrix::operator= (DenseMatrix const& that)
{
	if (this != &that) {          // prevent from self assignment
		data_.clear();             // delete the old data first
		data_.shrink_to_fit();
		rows_ = that.rows_;
		cols_ = that.cols_;
		data_ = std::vector<value_type>(rows_ * cols_, 0.0);  // allocate new data
		for (size_type i{0}; i < rows_; ++i) {	// copy the data
			for (size_type j{0}; j < cols_; ++j) {
				data_[i*cols_ + j] = that(i, j);
			}
		}
	}
	return *this;
}

DenseMatrix::size_type DenseMatrix::rows () const
{
	return rows_;
}

DenseMatrix::size_type DenseMatrix::cols () const
{
	return cols_;
}

void DenseMatrix::mv (Vector const& x, Vector& y) const
{
	assert (rows_ == y.size() && cols_ == x.size());
	for (int i{0}; i < rows_; ++i){
		for (int j{0}; j < cols_; ++j){
			y[i] += data_[cols_ * i + j] * x[j];
		}
	}
}

void DenseMatrix::scale (double const factor)
{
	for (size_type i{0}; i < rows_; ++i) {
		for (size_type j{0}; j < cols_; ++j) {
			data_[i*cols_ + j] *= factor;
		}
	}
}

DenseMatrix prod (Vector const& vec1, Vector const& vec2)
{
	DenseMatrix m{vec1.size(), vec2.size()};
	for (DenseMatrix::size_type i{0}; i < vec1.size(); ++i) {
		for (DenseMatrix::size_type j{0}; j < vec2.size(); ++j) {
			m(i, j) = vec1[i] * vec2[j];
		}
	}
	return m;
}

} // end namespace scprog

scprog::DenseMatrix operator* (scprog::DenseMatrix const& lhs, scprog::DenseMatrix const& rhs)
{
	scprog::DenseMatrix tmp{lhs};
	return tmp *= rhs;
}

scprog::DenseMatrix operator- (scprog::DenseMatrix const& lhs, scprog::DenseMatrix const& rhs)
{
	scprog::DenseMatrix tmp{lhs};
	return tmp -= rhs;
}

