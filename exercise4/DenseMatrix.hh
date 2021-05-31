#pragma once

#include "Vector.hh"

class Vector;

class DenseMatrix {
	std::size_t rows_, cols_;
	std::vector<double> data_;

public:
	DenseMatrix (std::size_t m, std::size_t n);
	DenseMatrix (std::size_t m, std::size_t n, std::vector<double> data);
	double& operator() (std::size_t i, std::size_t j);
	const double &operator() (std::size_t i, std::size_t j) const;
	std::size_t rows() const;
	std::size_t cols() const;
	void mv (Vector const& x, Vector& y) const;
};

DenseMatrix operator+ (DenseMatrix const A, DenseMatrix const B);