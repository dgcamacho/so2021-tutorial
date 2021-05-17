# Exercise sheet 4 (May 19th 2021)

## Task 1
What is the error (if any) in the following function definitions?
```c++
(a) double func (double) { return (2*double); }
(b) double func (double x) {return 2 * x};
(c) double func( double x) { x *= 2; }
(d) double& func (double x) { return x; }
(e) double func (double& x) { return &x; }
(f) double &func(double& x){ return x; }
```

## Task 2
We want to develop a small linear algebra framework that we will modify, extend, and apply to
algorithms in the following exercise sheets.

1. A vector type representing the space $`\mathbb{R}^n`$ with dynamic dimension $`n\in\mathbb{N}`$
2. A dense matrix type representing the space $`\mathbb{R}^{m\times n}`$ with dynamic dimension
   $`m\in\mathbb{N}`$ and $`n\in\mathbb{N}`$

### 2.1 Implementation of a Vector Class
Write a class `Vector` containing a `std::vector<double>` for the vector coefficients. The class
should provide the following methods:

- A constructor `Vector (std::size_t size)` that initializes the vector with the given length `size`
  and values `0`.
- An access method for the coefficients `double& operator[] (std::size_t i)`.
- Access to the size by `std::size_t size () const`.
- What else you think is useful.

A template for the class can be found in `material/Vector.hh`.

:bulb: `const` at the end of a member-function declaration means that this function can be called on
objects that are constant, i.e., marked with the `const` qualifier.


### 2.2 Implementation of a Matrix Class
Implement a class `DenseMatrix` that stores its shape as two `std::size_t` member variables and a
`std::vector<double>` representing the matrix coefficients, using a row-wise storage pattern. The
class should provide the following methods:

- A constructor `DenseMatrix (std::size_t rows, std::size_t cols)` to initialize a matrix of size
  `rows x cols` with values `0`.
- An access method for the coefficients `double& operator() (std::size_t i, std::size_t j)`.
- Access to number of rows and number of columns, i.e., `std::size_t rows () const` and
  `std::size_t cols () const`.
- Matrix-Vector multiplication `y = A*x` by `void mv (Vector const& x, Vector& y) const`.
- What else you think is useful.

A template for the class can be found in `material/DenseMatrix.hh`.

### Implementation Details
For the implementation follow a splitting of declaration and definition:

1. Create *header* files called `Vector.hh` and `DenseMatrix.hh`.
2. Put the class **definition** and the member-function **declarations** into this file. (Don't
   forget the include guards)
3. Create a corresponding *source* file called `<class>.cc`.
4. Include the header file in this source file.
5. Implement all previously declared functions in the source file.

### 2.3 The main method
In order to test your implementation, use the provided source file `material/task2.cc`.

1. Compile all individual source files to object files using the compiler option `-c`
2. Link together all object files to create an executable

These two steps need to be done with the following commands:
```bash
c++ -O3 -c <source1>.cc -o <source1>.o
c++ -O3 -c <source2>.cc -o <source2>.o
...
c++ <source1>.o <source2>.o... -o task2
```

or in one step
```bash
c++ -O3 <source1>.cc <source2>.cc... -o task2
```

3. Run the code and see a simple time measurement


## Task 3 (LU-Decomposition) - Submit for review :pencil:

### 3.1 Matrix factorization
Implement a class `LU` that performs and stores a LU factorization of a given matrix.
The class should provide the following methods:

- Compute the LU factorization: `void compute (DenseMatrix const& m)` of the given matrix `m` and store the
  result in an internal factorization matrix.
- Solve the linear system $`Ax=b`$: `void apply (Vector const& b, Vector& x) const`, by forwards and backwards
  application of the L-U factors.

A template for this class can be found in `material/LU.hh`.

### 3.2 Example linear system
Test your class by writing a program that solves the following linear system:

```math
    \begin{pmatrix}
      2 & -1 & 0\\
      -1 & 2 & -1\\
      0 & -1 & 2
    \end{pmatrix}
    \begin{pmatrix}
    x_1\\
    x_2\\
    x_3
    \end{pmatrix}
    =
    \begin{pmatrix}
    1\\
    1\\
    1
    \end{pmatrix}.
```

Test for correctness of the result by computing the residual $`r = b - Ax`$.

### Resources

- [Wikipedia:LU_decomposition](https://en.wikipedia.org/wiki/LU_decomposition)

### Submission
This exercise can be submitted for review. Please follow the general instructions given in the [README.md](/README.md)
page. In summary: 1. create a new branch `<zih-id>/exercise4`, 2. inside the folder `exercise4/` add
your solution: `task3.cc`, 3. `git add` and `git commit` your added and changed files, 4. push your
branch to the remote repository by `git push origin <zih-id>/exercise3`, 5. create a merge request.

**Deadline for the submission: end of 2021/06/02**


## Extra Task 4 (GotW-78: Operators, Operators Everywhere)
See [GotW #78](http://www.gotw.ca/gotw/078.htm).

1. What is the greatest number of plus signs (`+`) that can appear consecutively, without whitespace, in a
valid C++-program?

*Note:* Of course, plus signs in comments, preprocessor directives and macros, and literals don't count.
That would be too easy.

2. **Guru Question**: Similarly, what is the greatest number of each the following characters that can appear
consecutively, without whitespace, outside comments in a valid C++-program?
  - `&`,
  - `<`,
  - `|`.

For example, the code `if (a && b)` trivially demonstrates two consecutive `&` characters in a
valid C++-program.
