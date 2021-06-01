# include "LU.cc"
# include "Vector.cc"
# include "DenseMatrix.cc"

int main() {
    // Initialize the Matrix A and the rhs vector b
    scprog::DenseMatrix A = scprog::DenseMatrix(3, 3);
    A(0,0) = 2; A(0, 1) = -1;
    A(1, 0) = -1; A(1, 1) = 2; A(1, 2) = -1;
    A(2, 1) = -1; A(2, 2) = 2;

    scprog::Vector b = scprog::Vector(3);
    b[0] = b[1] = b[2] = 1;

    // compute the LU-factorization
    scprog::LU lu;
    lu.compute(A);

    // and solve the associated linear equation
    scprog::Vector x = scprog::Vector(3);
    lu.apply(b, x);

    // calculate residual
    scprog::Vector y = scprog::Vector(3);
    A.mv(x, y);
    scprog::Vector r = b - y;

    std::cout << (r.is_null() ? "Result is 0." : "Result is not 0.");
    r.print();
}