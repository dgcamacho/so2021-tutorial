#include "DenseMatrix.hh"
#include "Vector.hh"

#include <cassert>
#include <iostream>
#include <vector>

namespace scprog {

DenseMatrix::DenseMatrix (size_type const rows, size_type const cols)
	: rows_(rows), cols_(cols), data_(std::vector<value_type>(rows*cols,0.0))
	{}
		
DenseMatrix::DenseMatrix () : DenseMatrix::DenseMatrix(0,0) {}

// operators
DenseMatrix::value_type& DenseMatrix::operator() (size_type const i, size_type const j)
{
  return data_[i*cols_+j];
}

DenseMatrix::value_type const& DenseMatrix::operator() (size_type const i, size_type const j) const
{
  return data_[i*cols_+j];
}

// sets a specific value
void DenseMatrix::setValue (size_type const i, size_type const j, value_type value)
{
  data_[i*cols_+j] = value;
}

// initializes a matrix with all given values 
// values need to be given row-wise
void DenseMatrix::initialize (std::vector<value_type> const& allValues)
{
  if (data_.size() == allValues.size())
  {
	data_ = allValues;
  } else {
	std::cout << "Could not initialize matrix due to size incompatibility" << std::endl;
  }	
}

DenseMatrix::size_type DenseMatrix::rows () const
{
  return rows_;
}

DenseMatrix::size_type DenseMatrix::cols () const
{
  return cols_;
}

// matrix-vector multiplication
// x is multiplied with matrix A and result saved in y
void DenseMatrix::mv (Vector const& x, Vector& y) const
{
  for (std::size_t i=0; i<rows_; ++i) {
	for (std::size_t j=0; j<cols_; ++j) {
	  y[i] += data_[i*cols_+j]*x[j];
	}
  }
}
	
// print matrix
void DenseMatrix::print () const
{
  std::cout << "matrix print" << std::endl;
  for (std::size_t i=0; i<rows_; i++)
  {
	for (std::size_t j=0; j<cols_; j++)
	{
	  std::cout << data_[i*cols_+j] << "\t";
	}
	std::cout << std::endl;  
  }      	
}

} // end namespace scprog
