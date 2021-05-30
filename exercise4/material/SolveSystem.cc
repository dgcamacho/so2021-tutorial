#include "DenseMatrix.hh"
#include "LU.hh"
#include "Vector.hh"

#include <iostream>
#include <vector>

int main()
{
  scprog::DenseMatrix A = scprog::DenseMatrix(3,3);
  std::vector<double> const vec{2.0, -1.0, 0.0, -1.0, 2.0, -1.0, 0.0, -1.0, 2.0};    // example 1
//  std::vector<double> const vec{2.0, -1.0, -2.0, -4.0, 6.0, 3.0, -4.0, -2.0, 8.0}; // example 2
//  std::vector<double> const vec{1.0, 2.0, 4.0, 2.0, 3.0, 8.0, -1.0, -3.0, -1.0};   // example 3
  A.initialize(vec);
  
  std::cout << "matrix A" << std::endl;
  A.print();

  scprog::Vector b = scprog::Vector(3);
  std::vector<double> const vec2{1.0, 1.0, 1.0};
  b.initialize(vec2);
  
  std::cout << "Vector b" << std::endl;
  for (std::size_t i=0; i<3; ++i)
  {
	std::cout << b[i] << std::endl;  
  }
  
// ... is there a better way to initialize the values of matrix A and vector b?
// ... instead of writing this whole set of new member functions as I did?
  
  scprog::Vector x(3);
  scprog::Vector y(3);
    
  scprog::LU lu; 
  lu.compute(A);
  lu.apply(b,x);
  
  std::cout << "\n Vector x" << std::endl;
  for (std::size_t i=0; i<3; ++i)
  {
	std::cout << x[i] << std::endl;  
  }
  
  // check:
  A.mv(x,y);
  
  scprog::Vector r = b - y;
  bool isAboutZero = true;
  std::cout << "\nResidual" << std::endl;
  for (std::size_t i=0; i<3; ++i)
  {
	std::cout << r[i] << std::endl;  
	isAboutZero = isAboutZero && (abs(r[i]) < 1e-14);
  }
  if (isAboutZero)
    std::cout << "\nThe residual is equal to Zero (given the tolerance 1e-14)" << std::endl;
	  
}
