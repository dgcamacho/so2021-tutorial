# Exercise sheet 8 (June 23rd 2021)

## Task 1 (Functors)
Write a functor `Scale` that multiplies an assigned value with a constant factor. This constant factor
is stored as member variable in the functor and is initialized in the constructor. The `operator()` receives a
reference to the value and scales this argument (using pass-by-reference).

Use the STL algorithm `std::for_each` to scale the values of a `std::array`, or `std::vector`.

### Note
- The functor should not return the result, but change its argument that is passed-by-reference!
- In order to use `std::for_each` you need to include the header `<algorithm>`.

### Resources
- [cppreference:for_each](https://en.cppreference.com/w/cpp/algorithm/for_each)


## Task 2 (Iterators)
Do the following on a container, e.g. a `std::vector`, with `int`s, using standard function objects, function
adapters, algorithms, and maybe also some own function objects:
1. Find all values which are larger than a certain value.
2. Find all values which are not equal to certain value.
3. Multiply all values with a certain factor.
4. Compute the maximums norm.
5. Fill container with elements in the reverse order as the input container.


## Task 3 (Iterators)
1. Write an iterator `integer_range_iterator` that always returns an integer on dereferencing and increments this
integer when incrementing the iterator. Thus, when you loop over all values of the iterator you get an
increasing sequence of numbers, without storing this sequence explicitly. Provide a constructor, that takes the
initial value of the integer that is incremented. Example of usage:
```c++
for (auto it = integer_range_iterator(0); it != integer_range_iterator(10); ++it)
  std::cout << *it << " ";
```
This should print
```
0 1 2 3 4 5 6 7 8 9
```
Implement the dereferencing operator, increment operator and comparison operators.

2. Write a *pseudo-container* `integer_range`, that has just two member functions `begin()` and `end()` returning
the `integer_range_iterator` of the begin and end of the container. The values begin and end should
be given in the constructor of the container.

### Note
- A word *pseudo-container* here in this exercise refers to a container that does not store all its elements
  directly, but provides a way to iterate over all its values.
- (optional) In addition to the `begin()` and `end()` member-function, you could easily implement element-access functions
  `operator[]` and size functions for the `integer_range` container. What about mutable access functions? Can you implement
  the whole interface of a `std::vector`?


## Task 4 (Lagrange Polynomials) - Submit for review :pencil:

### Part 1 (Class Templates)
Implement a class template `Polynomial`, representing a polynomial `$p^{(n)}(x)`$ of degree `n`. In the template parameters
of that class you should specify the numerical type, i.e., the type of $`x`$, and the polynomial degree `n`.

- The class should be constructible from a `std::array`.
- Implement an `operator()` for the evaluation of the polynomial function.
- Additionally, implement an `operator*= (T const& alpha)` with `T` the numerical type, to scale the
  polynomial by a given factor `alpha`.

### Part 2 (Function Templates)
- Implement a function `derivative(...)` that expects a `Polynomial` of degree `n` as argument, computes
  the first derivative and returns this as a `Polynomial` of degree `n-1`.
- Write arithmetic operator `+`, `-`, and `*` for polynomials of degree `n` and `m`. What is the
  corresponding return type?

### Part 3 (Lagrange Interpolation)
- Write a function `lagrangeBasis(nodes, x)` that computes for a given set of Lagrange nodes $`\{x_i\}`$, represented as
  `std::array<double,N>`, the corresponding Lagrange basis polynomials $`l_i(x)`$ evaluated at $`x`$.
- The Lagrange interpolation polynomial $`L(f)`$ is a linear combination of the basis polynomials with function evaluations. Let $`f(x)`$ be
  a given function. Then

```math
L(f)(x) = \sum_{i=1}^N y_i l_i(x)
```

with $`y_i=f(x_i)`$.

- Implement a test routine to validate the lagrange basis and interpolation.

### Resources
- An explanation of the Lagrange polynomials can be found at
[Wikipedia](https://en.wikipedia.org/wiki/Lagrange_polynomial).


## Extra Task 5 (Algorithms)
What does the following algorithm implement?
```c++
template <class It>
It ALGORITHM2 (It first, It last)
{
  if (first == last)
    return last;

  It result = first;
  while (++first != last) {
    if (!(*result == *first) && ++result != first) {
      *result = *first; // or: ... = std::move(*first)
    }
  }
  return ++result;
}
```
Describe the requirements on the input types.