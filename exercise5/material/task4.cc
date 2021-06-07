#include "CRSMatrix.hh"

int main()
{
    scprog::CRSMatrix<double> A(3, 3, 3);
    A.add(1, 2, 3);

    return 0;
}
