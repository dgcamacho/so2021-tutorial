# Exercise sheet 2

## Task 1 (Floating-point numbers)
1. What is the difference between `float` and `double`?
2. Assume the following program needs 1 second to run:
```c++
int main()
{
  double x = 1.0e8;
  while (x > 0)
  {
    --x;
  }
}
```
How long would it run if you replace `double` by `float`? Why?

3. Look at the following code example:
```c++
#include <cassert>
int main()
{
  using T = float; // a type-alias
  T a = 0.15 + 0.15;
  T b = 0.1 + 0.2;
  assert(a == b);
  assert(a >= b);
}
```
where `assert` is a macro resulting in an error if the argument evaluates to `false`. What is the effect of the
program? What happens if we change `float` to `double`? Why?

### Resources
- https://en.wikipedia.org/wiki/Floating-point_arithmetic
- https://en.wikipedia.org/wiki/IEEE_754


## Task 2 (Control structures)
Get familiar with control structures in C++, i.e. `if`, `else`, `for`, `do`, `while`, `switch`, `case`.
1. Rewrite the following `while`-loop by a `for`-loop:
```c++
int log10 = 0;
double num = 12345.0;
while (num >= 10.0) {
  num /= 10.0;
  ++log10;
}
```

2. What is the error in the following statements?

  i.
```c++
  for (int j = 0, j < 10, ++j)
    std::cout << j;
```
  ii.
```c++
int n, sum = 0;
do
{ std::cin >> n; sum += n; }
while (n > 0)
```
  iii.
```c++
int n = 2, m;
while (n < 10)
  m *= n, ++n;
```
  iv.
```c++
unsigned long n = 0;
int cnt = 1;
do
  n += cnt;
  cnt++;
while (n < 100);
```

3. Write a C++-program that calculates and prints the sum of the squares of the first $`n`$ positive integers, i.e.
```math
1^2 + 2^2 + 3^2 + 4^2 + ... + n^2
```
while a positive integer is read from the keyboard. Use the standard stream operator `std::cin >> ...` and
`std::cout << ...` from `<iostream>` for reading and writing.

### Resources
- [if-then-else](https://en.cppreference.com/w/cpp/language/if), [switch-case](https://en.cppreference.com/w/cpp/language/switch),
  [for-loop](https://en.cppreference.com/w/cpp/language/for), [while-loop](https://en.cppreference.com/w/cpp/language/while),
  [do-while-loop](https://en.cppreference.com/w/cpp/language/do)
- [std::cout](https://en.cppreference.com/w/cpp/io/cout), [std::cin](https://en.cppreference.com/w/cpp/io/cin)


## Task 3 (C++ Expressions)
We have discussed *literals*, *variables*, *number conversion* and *initialization* in the lecture.
Print the value of the variable after the initialization and discuss why and how this is given.

1. `double x = 42.0f:`
2. `float x = 1e-50;`
3. `double x = 1/2;`
4. `double x = 1.0/2;`
5. `int x = -3ul + 4;`


## Task 4 (Power iteration) - Submit for review :pencil:
Write a program to approximate the largest eigenvalue $`\sigma > 0`$ and corresponding eigenvector
$`r\in \mathbb{R}^n`$ for a given positive-definite matrix $`A\in \mathbb{R}^{n\times n}`$. Therefore,
implement the power-iteration:

- Given a random initial vector $`r^{(0)}\in\mathbb{R}^n`$ that is not in the matrix kernel ($`Ar^{(0)} \neq 0`$).
- For $`k > 0`$ compute iteratively an approximation $`r^{(k)}:=\frac{Ar^{(k−1)}}{\|Ar^{(k−1)}\|}`$, with
  $`\|v\|^2:=\sum_{i=0}^{n-1} v_i^2`$ the Euclidean norm of a vector $`v\in \mathbb{R}^n`$.

An approximation of the corresponding eigenvalue is given by the Rayleigh quotient
$`\sigma(A,r) := \langle r,Ar\rangle / \langle r,r\rangle`$, with $`\langle r,s\rangle := \sum_{i=0}^{n-1}r_i s_i`$ the standard
Euclidean dot product. Follow the given steps in the implementation:

a) Write a function `rayleigh_quotient(A, r)` that computes and returns the Rayleigh quotient $`\sigma(A,r)`$

b) Implement a function `find_initial_value(A)` that returns to a given matrix $`A`$ an appropriate
   initial value $`r^{(0)}`$. Therefore, use the functions `std::rand()` (and `std::srand()`), see below.

c) Write a function `power_method(A, k)` to approximate the eigenvector $`r^{(k)}`$ iteratively and print
   in each step the Rayleigh quotient $`\sigma(A,r^{(k)})`$.

d) Finally, implement a `test(A, r, sigma)` that computes and prints the approximation error $`Ar−\sigma r`$
   in an appropriate norm.

Test your program with the following matrices with $`k= 20`$ iterations:

```math
    B = \begin{pmatrix}
        3&0&0\\
        0&1&0\\
        0&0&1
    \end{pmatrix}\quad
    C = \begin{pmatrix}
        4&-1&-1\\
        0.5&2&-1\\
        0&0&1
    \end{pmatrix}
```

### Remarks
- To represent the matrix and vectors, either use a static (multi-dimensional) array or any of the other
  data-structures discussed in the lecture or tutorial.
- Depending on the data-structure, you might need to pass additional information (like the size) to the functions.
- Remember: You cannot return directly raw arrays. Maybe you need to provide an output-parameter instead.
- In order to compute the dot product and the norm add a corresponding function. The required `sqrt` function can be found in the include file `<cmath>` and is called `std::sqrt`.

### Submission
This exercise can be submitted for review. Please follow the general instructions given in the [README.md](/README.md)
page. In summary: 1. create a new branch `<zih-id>/exercise2`, 2. inside the folder `exercise2/` add
your solution: `task4.cc`, 3. `git add` and `git commit` your added and changed files, 4. push your
branch to the remote repository by `git push origin <zih-id>/exercise2`, 5. create a merge request.

**Deadline for the submission: end of 2021/05/12**

### Resources
- [Power iteration](https://en.wikipedia.org/wiki/Power_iteration)
- [Rayleigh quotient](https://en.wikipedia.org/wiki/Rayleigh_quotient)
- [Arrays](https://en.cppreference.com/w/c/language/array)
- [std::rand](https://en.cppreference.com/w/cpp/numeric/random/rand)
- [std::sqrt](https://en.cppreference.com/w/cpp/numeric/math/sqrt)
