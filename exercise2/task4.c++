#include <iostream>
#include <cmath>
#include <ctime>

void matvec (int const size, double const mat[], double const vec[], double prod[])
{
    // matrix-vector product, prod is the output vector
    for (int i{0}; i < size; i++) 
    {
        prod[i] = 0.0;
        for (int j{0}; j < size; j++)
        {
            prod[i] += mat[i*size + j] * vec[j];
        }
    }  
}

void copy (int const size, double const vec1[], double vec2[])
{
    // copy vector vec1 into vector vec2
    for (int i{0}; i < size; i++)
    {
        vec2[i] = vec1[i];
    }
    
}

void vec_num_prod (int const size, double vec[], double const num)
{
    // multiply a vector by a number
    for (int i{0}; i < size; i++)
    {
        vec[i] *= num;
    }
}

void substract (int const size, double const vec1[], double const vec2[], double diff[])
{
    // substract two vectors, diff is the result vector
    for (int i{0}; i < size; i++)
    {
        diff[i] = vec1[i] - vec2[i];
    }   
}

double dot_product (int const size, double const vec1[], double const vec2[])
{
    // dot product of two vectors
    double sum{0};
    for (int i{0}; i < size; i++)
    {
        sum += vec1[i] * vec2[i];
    }
    return sum;
}

double norm (int const size, double const vec[])
{
    // euclidian norm of a vector
    return std::sqrt(dot_product(size, vec, vec));
}

double rayleigh_quotient (int const size, double const mat[], double const vec[])
{
    // computes rayleigh quotient
    double mat_vec_prod[size]{};
    matvec(size, mat, vec, mat_vec_prod);
    return dot_product(size, vec, mat_vec_prod) / dot_product(size, vec, vec);
}

void find_initial_value (int const size, double const mat[], double vec[])
{
    // finds a random vector vec outside the kernel of the matrix mat
    // first line seeds with current time
    std::srand(std::time(nullptr));
    double prod[size]{};
    do
    {
        for (int i{0}; i < size; i++)
        {
            vec[i] = std::rand();
        }
        matvec(size, mat, vec, prod);
    } while (norm(size, prod) == 0);
}

void power_method (int const size, int const k, double const mat[], double vec[])
{
    // power method to find eigenvector; vec2 serves as temporary copy of vec to not lose its information
    double vec2[size]{};
    find_initial_value(size, mat, vec);
    copy(size, vec, vec2);
    for (int i{1}; i <= k; i++)
    {
        matvec(size, mat, vec, vec2);
        vec_num_prod( size, vec2, 1/norm(size, vec2) );
        copy(size, vec2, vec);
        std::cout << "Rayleigh quotient in " << i << "th iteration: " << rayleigh_quotient(size, mat, vec) << std::endl;
    }
}

void test (int const size, double const mat[], double const vec[], double const sigma)
{
    // print euclidian norm of eigenvector error
    double prod[size]{};
    double multiple[size]{};
    double difference[size]{};
    matvec(size, mat, vec, prod);
    copy(size, vec, multiple);
    vec_num_prod(size, multiple, sigma);
    substract(size, prod, multiple, difference);
    std::cout << "2-norm of error: " << norm(size, difference) << std::endl;
}

int main() 
{
    int const size{3};
    int const k{20};
    double const B[size*size]{3.0,0.0,0.0,  0.0,1.0,0.0,  0.0,0.0,1.0};
    /* alternative code if the matrix B should be inserted by user
    double B[size*size]{};
    std::cout << "Enter matrix B componentwise in row-order: ";
    for (int  i{0}; i < (size*size); i++)
    {
        std::cin >> B[i];
    }
    std::cout << std::endl;
    */
    double eigenvector_b[size]{};
    std::cout << "matrix B:" << std::endl;
    power_method(size, k, B, eigenvector_b);
    std::cout << "eigenvector for matrix B: ";
    for (int i{0}; i < size; i++)
    {
        std::cout << eigenvector_b[i] << " ";
    }
    std::cout << std::endl;
    test(size, B, eigenvector_b, rayleigh_quotient(size, B, eigenvector_b));

    double const C[size*size]{4.0,-1.0,-1.0,  0.5,2.0,-1.0,  0.0,0.0,1.0};
    double eigenvector_c[size]{};
    std::cout << "matrix C:" << std::endl;
    power_method(size, k, C, eigenvector_c);
    std::cout << "eigenvector for matrix C: ";
    for (int i{0}; i < size; i++)
    {
        std::cout << eigenvector_c[i] << " ";
    }
    std::cout << std::endl;
    test(size, C, eigenvector_c, rayleigh_quotient(size, C, eigenvector_c));
}