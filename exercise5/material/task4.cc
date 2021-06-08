#include "CRSMatrix.hh"
#include "Vector.hh"

int main()
{
    std::vector<std::size_t> offset{2, 2, 2};
    std::vector<std::size_t> indices{0, 2, 1, 2, 0, 1};
    std::vector<double> values{1, 3, 2, -1, -4, -1};
    scprog::CRSMatrix<double> A(3, 3, 3);//, indices, values, offset);
    A.set(1, 1, 4);
    A.add(1, 1, 3);
    A.set(1, 2, 3);
    A.add(1, 2, 5);
    A.add(1, 0, 3);
    A.add(2, 0, 2);

    A.compress();

    std::vector<double> const x_vec = {3,1,2};
    scprog::Vector x(3);
    x.fill(x_vec, 3);
    scprog::Vector y(3);
    std::cout << "Now we are multiplying" << std::endl;
    A.mv(x, y);


    return 0;
}
