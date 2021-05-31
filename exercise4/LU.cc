#include "LU.hh"
#include <iostream>
#include <cassert>

void LU::compute (DenseMatrix const& m) {
	assert(m.cols() == m.rows());
	
	//variables for last iteration and for saving the factors
	DenseMatrix last = m;
	DenseMatrix L{m.rows(), m.cols()};
	double factor = 0;

	decomposition_ = m;

	//this loop implements the algorithm given on the
	//English Wikipedia page
	for (int n=0; n < m.rows() - 1; n++) {
		//revent division by zero
		assert(last(n,n) != 0);

		for (int i=n+1; i < m.rows(); i++) {
			for (int j=0; j < m.cols(); j++) {
				//fill i-th row
				factor = -last(i, n) / last(n, n);
				decomposition_(i, j) = last(i, j) + factor * last(n, j);
				L(i, n) = -factor;
			}
		}

		last = decomposition_;
	}

	//save the factors in the same matrix
	//as entries of L in the main diagonal are all = 1
	decomposition_ = decomposition_ + L;
}

void LU::apply (Vector const& b, Vector& x) const{
	double sum = 0;
	int size = x.size();

	//forward substitution
	for (int m=0; m < size; m++){
		sum = 0;

		for (int i=0; i < m; i++)
			sum += decomposition_(m,i) * x[i];

		x[m] = b[m] - sum;
	}

	//backward substitution
	for (int m = size - 1; m >= 0; m--){
		sum = 0;

		for (int i = size - 1; i > m; i--)
			sum += decomposition_(m,i) * x[i];
		
		x[m] = (x[m] - sum) / decomposition_(m, m);
	}
	
}