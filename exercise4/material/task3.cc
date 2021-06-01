#include <iostream>

#include "DenseMatrix.hh"
#include "LU.hh"
#include "Vector.hh"

int main () {
    scprog::DenseMatrix A(3,3);
    A(0,0) = 2;
    A(0,1) =-1;
    A(0,2) = 0;
    A(1,0) =-1;
    A(1,1) = 2;
    A(1,2) =-1;
    A(2,0) = 0;
    A(2,1) =-1;
    A(2,2) = 2;
    // A = {{2, -1, 0},{-1, 2, -1},{0, -1, 2}}
    
    std::cout << "A = " << std::endl;
    A.print();
    
    // compute LU decomposition
    scprog::LU lu(A.rows());
    lu.compute(A);

    std::cout << "\n---- LU(A): ----" << std::endl;
    lu.print();

    // to be sure that A is not modified
    std::cout << "\nA = " << std::endl;
    A.print();


    std::cout << "===================================== \nAPPLICATION" << std::endl;

    scprog::Vector b = scprog::Vector(3);
    b[0] = b[1] = b[2] = 1;
    std::cout << "b = ";
    b.print();

    scprog::Vector x = scprog::Vector(A.cols());
    
    lu.apply(b, x);

    std::cout << "x = ";
    x.print();

    std::cout << "===================================== \nRESIDUAL" << std::endl;
    scprog::Vector r = scprog::Vector(A.cols());
    A.mv(x, r);
    r = b - r;
    
    std::cout << "r = b - Ax = ";
    r.print();
    // << std::endl;

    return 0;
}