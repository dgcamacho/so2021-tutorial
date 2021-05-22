# Exercise 4

## Submission of Task 4

### Luise Zieger

Some words about my solution:

- Class LU:

    I implemented the member functions in the file LU.cc :

    - compute: compute the LU-decomposition of the matrix

    - apply: solve a linear system Ax = b for x by applying the LU-decomposition

I modified the following classes which where already implemented in previous tasks:

- Class Vector:

    I added two member functions:

    - operator-: compute the difference vector of two vectors

    - print: output as a line vector

- Class DenseMatrix:

    I added a default constructor (needed for initializing the decomposition_ attribute when initializing an instance of the LU class) and one additional member functions:

    - print:  rowwise output of a matrix

I wrote a main program in the file task3.cc which tests the implemented LU algorithm for a 3 x 3 test matrix.
