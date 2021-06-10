#include "CRSMatrix.hh"
#include "Vector.hh"

int main()
{
    // Implementing the test-case from exercise 6:
    //     ( 2, -1,  0)       (1)           (1)
    // A = (-1,  2, -1) ; x = (1) ==> A*x = (0)
    //     ( 0, -1,  2)       (1)           (1)
    
    scprog::CRSMatrix<double> A(3, 3, 3);
    A.set(0, 0, 2);
    A.set(0, 1, -1);
    A.set(1, 0, -1);
    A.set(1, 1, 2);
    A.set(1, 2, -1);
    A.set(2, 1, -1);
    A.set(2, 2, 2);

    A.compress();

    std::vector<double> const x_vec = {1,1,1};
    scprog::Vector x(3);
    x.fill(x_vec, 3);
    scprog::Vector y(3);
    A.mv(x, y);

    std::cout << "The resulting vector is \n";
    y.printV();


    return 0;
}
