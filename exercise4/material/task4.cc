#include "DenseMatrix.hh"
#include "LU.hh"
#include "Vector.hh"

#include <iostream>

using namespace scprog;

int main()
{
	DenseMatrix m{3, 3};
	Vector x{3}, b{3}, r{3};
	LU decomp{3};
	m(0, 0) = 2; m(0, 1) = -1; m(0, 2) = 0; 
	m(1, 0) = -1; m(1, 1) = 2; m(1, 2) = -1; 
	m(2, 0) = 0; m(2, 1) = -1; m(2, 2) = 2; 
	b[0] = 1; b[1] = 1; b[2] = 1; 
	
	decomp.compute(m);
	decomp.apply(b, x);

	// compute residual
	m.mv(x, r);
	r = b - r;
	std::cout << "residual b-Ax = ";
	for (int i{0}; i < 3; ++i) {
		std::cout << r[i] << " ";
	}
	std::cout << std::endl;
}