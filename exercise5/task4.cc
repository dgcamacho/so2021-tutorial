#include <iostream>
#include <cstdlib>

#include "SparseMatrix.hh"
#include "Vector.hh"

using namespace scprog;

int main() {
	CRSMatrix<double> matrix(3,3,3);
	
	matrix.set(0,0, 2);     matrix.set(0,1,-1); /*matrix.set(0,2, 0);*/
	matrix.set(1,0,-1);     matrix.set(1,1, 2);   matrix.set(1,2,-1);
	/*matrix.add(2,0, 0);*/ matrix.add(2,1,-1);   matrix.add(2,2, 2);
  
  //~ matrix.compress();
  
  std::cout << "Initial matrix:" << std::endl << matrix;
  
  matrix.add(2,1,1);
  std::cout << "After adding 1 to (2,1): " << std::endl << matrix;
  
  matrix.add(2,1,-1);
  std::cout << "After adding -1 to (2,1): " << std::endl << matrix;
  
  matrix.compress();
	
	Vector x(3);
	x[0] = 1; x[1] = 1; x[2] = 1;
  std::cout << "Calculating y=A*x" << std::endl << "A = " << std::endl << matrix << "x = " << x;
	Vector y(3);
	matrix.mv(x,y);
	
	std::cout << "y = " << y;
	
	return EXIT_SUCCESS;
}
