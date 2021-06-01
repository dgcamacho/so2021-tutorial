#include <bits/c++config.h>
#include <iostream>
#include <vector>

#include "DenseMatrix.hh"
#include "LU.hh"
#include "Vector.hh"

// Check whether the lu-decomposition returned the right result  
bool check_residual(scprog::DenseMatrix const& A, scprog::Vector const& b, 
                    scprog::Vector const& x) 
{
    scprog::Vector lhs(b.size());
    // calculate matrix-vector product on left hand side
    A.mv(x, lhs);
    // check whether left hand side is equal to right hand side
    if (!(b == lhs)) {
        // if not, print the difference and return false
        scprog::Vector res = b - lhs;
        res.printV();
        return 0;
    } else {
        // else, return true
        return 1;
    }
}

int main()
{
    // initialize the data-vector for the matrix of the given system of 
    // equations to solve
    std::vector<double> const A_data = { 2, -1,  0,
                                  -1,  2, -1,
                                   0, -1,  2 };

    // initialize the data-vector for the rhs-vector of the given sytem of 
    // equations to solve
    std::vector<double> const b_data = {1, 1, 1};

    // create and fill the corresponding DenseMatrix
    scprog::DenseMatrix A(3, 3);
    A.fill(A_data, 3, 3);

    // create and fill the corresponding Vector
    scprog::Vector b(3);
    b.fill(b_data, 3);

    // initialize the solution vector as size 3 with 0-entries
    scprog:: Vector x(3);

    // initialize the solver and solve the system of equations
    scprog::LU lu;
    lu.compute(A);

    lu.apply(b, x);

    // print the solution and check whether the solution is correct
    x.printV();
    bool solved = check_residual(A, b, x);
    return solved ? 0 : -1;
   
}
