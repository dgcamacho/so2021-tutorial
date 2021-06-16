#include <cstdlib>
#include <iostream>

#include "CRSMatrix.hh"
#include "Vector.hh"

using namespace scprog;

int main() {
	CRSMatrix<double> matrix(3,3,3);
	
	matrix.set(0,0, 2);     matrix.set(0,1,-1); /*matrix.set(0,2, 0);*/
	matrix.set(1,0,-1);     matrix.set(1,1, 2);   matrix.set(1,2,-1);
	/*matrix.add(2,0, 0);*/ matrix.add(2,1,-1);   matrix.add(2,2, 2);
  
  
  std::cout << "Initial matrix:" << std::endl << matrix;
  
  matrix.add(2,1,1);
  std::cout << "After adding 1 to (2,1): " << std::endl << matrix;
  
  matrix.add(2,1,-1);
  std::cout << "After adding -1 to (2,1): " << std::endl << matrix;
  
  matrix.compress();
  std::cout << "After compressing: " << std::endl << matrix;
	
	Vector x(3);
	x[0] = 1; x[1] = 1; x[2] = 1;
	Vector y(3);
  
	matrix.mv(x,y);
  std::cout << "Calculating y=A*x" << std::endl 
            << "A = " << std::endl << matrix
            << "x = " << x
            << "y = " << y;
	
	return EXIT_SUCCESS;
}
