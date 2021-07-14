# Exercise sheet 11 (July 14th 2021)

## Task 1 (Views)
A *view* is a class representing a subset or a transformation of the data of an object, like a container, without storing the actual values. This is very similar to *expression templates*. Also *expression templates* define a view onto some data, e.g., representing a scaled vector or the sum of two vectors. Thereby, only reference to the data is stored and the actual operation is done when accessing the view object, e.g., in form of an `operator[]` call.

For a `DenseMatrix` class (see directory `material/` of exercise sheet 4 or 7), implement a view onto the `i`'th row of the matrix:

- Add a member function `row(i) -> RowView` returning an object similar to a vector expression.
- The class `RowView` must thereby be constructed with a reference to the data of the matrix, or the matrix itself, and the row index.
- The `RowView` type has two member functions, a `size()` method returning the number of columns in the row and an `operator[](j)` accessing the `(i,j)`'th element in the matrix.
- Implement this `RowView` type in such a way that you can use it in any vector expression from the last exercise sheet. Tip: use a CRTP base class.
- (Advanced) Can you do the same for the `j`'th column and the diagonal of the matrix?
- (Advanced) When implementing the same for a `CRSMatrix`, the row vector might be a "sparse" vector. How to handle the sparsity, i.e., that not all entries are actually stored in the matrix, efficiently? Can you modify the vector expressions to also handle sparse vectors without traversing all the zero-entries?

## Task 2 (Metafunctions)
Implement the greatest common devisor (gcd) in multiple ways:

1. Write a generic function for integers (with generic integer type) to calculate the gcd of two integral numbers:

```math
gcd(a,b) := \left\{
  a & \text{ if b = 0}, \\
  gcd(b, a mod b) & \text{ otherwise}\right.
```

Write the function in the form
```c++
template <typename Integer>
Integer gcd (Integer a, Integer b) { ... }
```

(Advanced) What would be a (mathematically correct) constraint for the template parameters to be not too restrictive? How to formulate such a concept and how to implement the corresponding algorithm for the computation?

2. Implement a metafunction `gcd_meta` for the same algorithm using template meta-programming. The function should be of the form

```c++
template <int A, int B>
struct gcd_meta {
  static constexpr int value = ...;
};
```

The metafunction is then called by `gcd_meta<a,b>::value` with two integer number `a` and `b`. Compare your result with the value computed with the run-time function `gcd(a,b)`.

3. Implement the same metafunction using `constexpr` functions instead.
4. Compile your code with the commandline option `-S` to generate assembler output instead of an executable. Alternatively, use the Compiler Explorer https://godbolt.org and examine the output. Verify the the metafunctions are actually computing the result at compiletime.


## Task 3 (Type Traits)

Write a typefunction `is_const : T -> bool` that returns `true` is the type `T` has the `const` qualifier, otherwise `false`. Additionally, implement a typefunction `add_const : T -> T const` that adds the `const` qualifier to a given type `T`.


## Task 4 (Type Lists)

Implement a list of types, i.e., a so called meta-type-list. It has the form

```c++
template <typename H, typename T>
struct List
{
  using Head = H;   // the type at the fron of the list
  using Tail = T;   // the remaining type in form of a list List<...>
}
```

By specifying `H` and `T` you can now concatenate types, e.g., a list of floating-point types:

```c++
using FloatingPointTypes = List<float, List<double, long double>>;
```

or by using a *final type* `NullType` indicating the end of the list:

```c++
struct NullType {};
using FloatingPointTypes
  = List<float,
      List<double,
        List<long double,
          NullType
        >
      >
    >;
```

Implement metafunctions `insert`, `append`, `delete`, and `size` for this type list, to insert a new type at a specific position in the list, to insert a type at the end of the list, to remove a type at a specific position from the list and to return the number of entries in the list, respectively.

### Example
The implementation of the `append` metafunction might look like this:

```c++
template <typename L, typename Type>
struct Append { // primary template
  using type = List< typename L::Head,
                     typename Append<typename L::Tail, Type>::type >;
};

template <typename Type>
struct Append<NullType, Type> { // template specialization
  using type = List< Type, NullType >;
};
```
