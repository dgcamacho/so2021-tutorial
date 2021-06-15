#include <iostream>

#include "CRSMatrix.hh"
#include "binary_test.cc"


int main() {
    // run tests for binary search
    binary_search_tests();
    
    // create some matrix and print it
    CRSMatrix<int> A(4, 4, 2);

    A.set(0, 0, 10);
    A.set(0, 3, 20);
    A.set(2, 3, 30);
    A.add(2, 3, 1);
    A.set(3, 0, 40);
    std::cout << A.nc() << std::endl;
    std::cout << A.nr() << std::endl;
    std::cout << A.max_nz() << std::endl;
    A.print();
    A.set(0, 3, 0);
    A.compress();
    std::cout << A.nc() << std::endl;
    std::cout << A.nr() << std::endl;
    std::cout << A.max_nz() << std::endl;
    A.print();
    A.print_nonsparse();
    A.increase_max_nonzeros(3);
    A.set(2, 0, 50);
    A.add(2, 2, 60);
    A.print();
    return 0;
}