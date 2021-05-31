#pragma once

#include "Vector.hh"
#include "DenseMatrix.hh"

class DenseMatrix;

class LU {
	DenseMatrix decomposition_;

public:
	LU(std::size_t rows, std::size_t cols) : decomposition_(rows, cols) {
	}; //initialises the decomposition matrix
	void compute (DenseMatrix const& m);
	void apply (Vector const& b, Vector& x) const;
};