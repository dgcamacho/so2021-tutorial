#include <cassert>
#include <cmath>

#include "Vector.hh"
#include "DenseMatrix.hh"

DenseMatrix::DenseMatrix (std::size_t m, std::size_t n) {
	data_ = std::vector<double>(m*n);
	rows_ = m;
	cols_ = n;
}

DenseMatrix::DenseMatrix (std::size_t m, std::size_t n, std::vector<double> data) {
	data_ = data;
	rows_ = m;
	cols_ = n;
}

double& DenseMatrix::operator() (std::size_t i, std::size_t j) {
	return data_[i*cols_ + j];
}

const double &DenseMatrix::operator() (std::size_t i, std::size_t j) const {
	return data_[i*cols_ + j];
}

DenseMatrix operator+ (DenseMatrix const A, DenseMatrix const B) {
	assert((A.rows() == B.rows()) && (B.cols() == A.cols()));

	DenseMatrix result{A.rows(), A.cols()};

	for (int i=0; i < A.rows(); i++)
		for (int j=0; j < B.cols(); j++)
			result(i,j) = A(i,j) + B(i,j);

	return result;
}

std::size_t DenseMatrix::rows() const {
	return rows_;
}

std::size_t DenseMatrix::cols() const {
	return cols_;
}

void DenseMatrix::mv (Vector const& x, Vector& y) const {
	for (int i=0; i < rows_; i++)
		for (int j=0; j < cols_; j++)
			y[i] += data_[i*cols_ + j] * x[j];
}