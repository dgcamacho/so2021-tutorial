#include <iostream>

#include "DenseMatrix.hh"
#include "LU.hh"
#include "Vector.hh"

int main () {
    scprog::Vector v = scprog::Vector(3), w = scprog::Vector(3);
    v[0] = v[1] = v[2] = 1;
    w[0] = 1;
    w[1] = 2;
    w[2] = 3;

    std::cout << "v = ";
    v.print();

    std::cout << "w = ";
    w.print();

    scprog::Vector res = 3 * w;

    std::cout << "res = ";
    res.print();

    std::cout << "dot product v * w = " << dot(v,w) << std::endl;
    std::cout << "norm      || v || = " << norm(v) << std::endl;

    return 0;
}