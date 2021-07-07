# Exercise sheet 10 (July 7th 2021)

## Task 1 (Expression templates)

Implement binary vector expressions for the binary operators `+` and `-`, with a `Vector` class
as basic data structure (see exercise sheet 5, 6, or 7 and its solution/material). Additionally,
the *expression templates* should be implicitly convertible to `Vector`, i.e., add a corresponding
converting constructor to the `Vector` class. The implementation should allow for expressions of
the following form without creating intermediate temporary vectors:

```c++
Vector a{...}, b{...}, c{...};
Vector t1 = a + b + c;
Vector t2 = a - a;
```

For the implementation, follow the code examples in the lecture.
Test your implementation, by providing some known results.


## Task 2 (Benchmarking)

We want to compare the *expression templates* implementation with a classical operator-overloading implementation.

1. Put the code for the two implementations in two different header files, named `VectorExpr.hh` and `VectorOverload.hh`. Make sure the classes are named differently.
2. Add functions `benchmark_expr()` and `benchmark_overload()` with the following semantics:

```c++
std::pair<bool,double> benchmark_xyz () {
  Vector a{...}, b{...}, c{...}; // create and initialize vectors of LARGE_SIZE
  bool pass = true;
  scprog::Timer t;
  for (int i = 0; i < MAX_ITER; ++i) {
    Vector sum = a + b + c;
    pass |= (sum[0] == VALUE_AT_SUM_0);
  }
  return {pass, t.elapsed()/MAX_ITER};
}
int main() {
  auto [pass,timing] = benchmark_xyz();
  // ...
}
```
using the `Timer` class from `Timer.hh` in the material folder.

3. Run the code and print the timing and whether the sum is correct to `std::cout`
4. Add a handcoded function for the sum of three vectors and compare the timings against the other
   two variants.
5. Modify the code to use the [Google benchmarking suite](https://github.com/google/benchmark):

```c++
#include <benchmark/benchmark.h>
static void benchmark_xyz (benchmark::State& state) {
  Vector a{...}, b{...}, c{...}; // create and initialize vectors LARGE_SIZE
  bool pass = true;
  for (auto _ : state) {
    Vector sum = a + b + c;
    pass |= (sum[0] == VALUE_AT_SUM_0);
  }
  assert(pass);
}

// Register the function as a benchmark
BENCHMARK(benchmark_xyz);
// Run the benchmark
BENCHMARK_MAIN();
```

### Remark
Either you install the google benchmark suite locally, or you use the online [Quick Bench](https://quick-bench.com/)
tool for this.


## Task 3

Extend the *expression templates* code to support scalar multiplication of vectors, i.e., `scalar * vector` and `vector [*/] scalar`. Again, no temporaries should be created during this operation and the assignment to a new vector.

Your code should support the following expressions:

```c++
Vector d{...}, e{...}, f{...};
double alpha{...};
Vector t3 = alpha * (d + e) + f;
Vector t4 = (d + e) / 2.;
```

(Optional) Benchmark your code against the classical operator-overloading approach, as in Task 2.

### Remark
Restrict yourself to the scalar number type `double` to not introduce some ambiguities with the expressions.


## Task 4 (Matrix-Vector product) - Submit for review :pencil:

Extend the *expression templates* library by a matrix-vector multiplication expression. Your code should
support the following expressions

```c++
Vector j{...}, k{...}, l{...};
DenseMatrix M{...};
CRSMatrix M2{...};
Vector t5 = j + M * (k - l);
Vector t6 = j + M2 * (k - l);
```

Create a class that implements the matrix-vector product row-wise by overloading the `operator[](std::size_t)`.
Test your code with the example of matrix and vector given in the previous exercise sheets.

### Remarks
- We do not expect you to implement general matrix-vector or matrix-matrix expressions. Thus, the `operator*` can
  be implemented for an explicit first type.
- The matrix-vector operation is different for `DenseMatrix` and for `CRSMatrix`. How can this be represented
  in the expression code?
- If you multiply a matrix with a complicated vector expression, this expression is evaluated completely for
  each row of the matrix. This might be inefficient. How to implement some kind of caching of the vector expression result?

### Submission

This exercise can be submitted for review. Please follow the general instructions given in the [README.md](/README.md)
page. In summary: 1. create a new branch `<zih-id>/exercise10`, 2. inside the folder `exercise10/` add
your solution: `task4.cc`, 3. `git add` and `git commit` your added and changed files, 4. push your
branch to the remote repository by `git push origin <zih-id>/exercise10`, 5. create a merge request.

**Deadline for the submission: end of 2021/07/14**
