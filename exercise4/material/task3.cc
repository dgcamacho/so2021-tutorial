#include <iostream>
#include "LU.hh"

using namespace scprog;

int main() {
    // initialize a 3 x 3 test matrix
    DenseMatrix A = DenseMatrix(3,3);
    A(0,0) = A(1,1) = A(2,2) = 2.0;
    A(0,1) = A(1,0) = A(1,2) = A(2,1) = -1.0;
    A(0,2) = A(2,0) = 0.0;
    std::cout << "A =" << std::endl;
    A.print();

    // initialize the rhs vector b
    Vector b = Vector(3);
    b[0] = b[1] = b[2] = 1;
    std::cout << "\nb = ";
    b.print();

    // initialize an instance of LU and compute the decomposition of A
    LU* lu = new LU();
    lu->compute(A);
    std::cout << "\nDecomposition: " << std::endl;
    lu->printLU();

    // solve Ax = LUx = b by applying the decomposition
    Vector x = Vector(3);
    lu->apply(b, x);
    std::cout << "\nSolve LUx = b for x:" << std::endl;
    std::cout << "x = "; 
    x.print();

    // test for correctness
    std::cout << "\nTest for correctness:" << std::endl;
    Vector Ax = Vector(3);
    A.mv(x, Ax);
    std::cout << "Residual r = b - Ax = ";
    (b - Ax).print();
}
