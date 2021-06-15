#include <iostream>

#include "CRSMatrix.hh"


int main() {
    CRSMatrix<int> A(3, 3, 3);
    A.set(0, 0, 2);  A.set(0, 1, -1);
    A.set(1, 0, -1); A.set(1, 1, 2);  A.set(1, 2, -1);
                     A.set(2, 1, -1); A.set(2, 2, 2);
    A.print_nonsparse();
    
    std::vector<int> x(3, 1);
    std::vector<int> y(3, 0);
    A.mv(x, y);

    std::cout << "Computed result is ";
    for (int i = 0; i < y.size(); ++i){
        std::cout << y[i] << ' ';
    }
    std::cout << std::endl;
    std::cout << "Exact result is 1 0 1 ." << std::endl;
    return 0;
}