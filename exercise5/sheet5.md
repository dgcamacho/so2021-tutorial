# Exercise sheet 5 (June 2nd 2021)

## Task 1
Which conversions are used in the following program in each expression?
```c++
struct X {
  int i;
  X(int); // constructor
  X operator+(int); // X + int
};

struct Y {
  int i;
  Y(X); // constructor
  Y operator+(X); // Y + X
  operator int(); // cast-to-int operator
};

inline X operator*(X,Y); // X * Y
inline int f(X); // f(X) -> int

int main() {
  X x = 1;
  Y y = x;
  int i = 2;

  i + 10;     y + 10;      y + 10 * y;
  x + y + i;  x * x + i;   f(7);
  f(y);       y + y;       106 + y;
}
```
Change the code to correct all errors and print the value of each expression.


## Task 2

In the following there are various overloads of `foo(.)` and `bar(.,.)` provided. Which of the function is called in the
main program, correspondingly. Are there ambiguities? First think about it, then implement and check yourself.
```c++
void foo(int a) {...};            // (a)
void foo(int& a) {...};           // (b)
void foo(int* a) {...};           // (c)
void foo(double a) {...};         // (d)
void bar(int a, int b) {...};     // (e)
void bar(float a, float b) {...}; // (f)

int main() {
  int a = 1;
  float b = 1.0f;
  double c = 1.0;

  foo(a);       // (1)
  foo(&a);      // (2)
  foo(1.0);     // (3)
  foo(b);       // (4)
  foo(&b);      // (5)
  foo(c);       // (6)

  bar(a, a);    // (7)
  bar(1.0, a);  // (8)
  bar(&a, a);   // (9)
  bar(b, b);    // (10)
  bar(c, c);    // (11)
  bar(b, c);    // (12)
  bar(a, b);    // (13)
}
```


## Task 3 (Arithmetic operators for Vectors)

For the class `Vector` from exercise sheet 4 implement the following arithmetic and assignment operators inside the class:

- `Vector& operator+=(Vector const&)` elementwise addition
- `Vector& operator-=(Vector const&)` elementwise subtraction
- `Vector& operator*=(value_type factor)` elementwise multiplication with `factor`
- `Vector& operator/=(value_type factor)` elementwise division by `factor`

Additionally implement the following functions outside the class and use the in-class methods for their implementation:

- `Vector operator+(Vector const&, Vector const&)` addition
- `Vector operator-(Vector const&, Vector const&)` subtraction
- `Vector operator*(Vector::value_type factor, Vector const&)` multiplication from the left with `factor`
- `Vector operator*(Vector const&, Vector::value_type factor)` multiplication from the right with `factor`
- `Vector operator/(Vector const&, Vector::value_type factor)` division from the right by `factor`


## Task 4 (Sparse Matrix) - Submit for review :pencil:

Implement a sparse matrix in CRS Format. Therefore, write a class `CRSMatrix<T>` parametrized with the element type `T` that provides the following
interface:

- A constructor with number of rows and number of columns and a third argument for the maximal
  number of nonzero entries per row.
- A type alias `value_type = T` (and a `size_type` alias as well)
- A function `void add (size_type i, size_type j, value_type value)` to add a nonzero entry at `(i,j)` to
  the matrix. If an entry already exists at this position, the values should be added up.
- A function `void set (size_type i, size_type j, value_type value)` to add a nonzero entry at `(i,j)` to
  the matrix. If an entry already exists at this position, the values should be replaced by the given `value`.
- A function `void compress ()` to remove all gaps and zeros in the internal storage.
- Matrix-Vector multiplication `y = A*x` by `void mv (Vector const& x, Vector& y) const`.

The strategy to implement insertion is as follows:

1. Create vectors `indices` and `values` of size *(maximum number of nonzeros per row) x (number of rows)* and type `std::vector<...>`
2. Create a vector `offset` of size *(number of rows)* and type `std::vector<...>` that contains the number of column entries already stored in each row, thus initialized to 0.
3. On insertion by `add` or `set` go to the corresponding position of the row in `indices` and `values` and traverse all stored column
   indices to find the position where to insert a new entry. Therefore, we assume that the column indices
   are sorted in each row. Thus, you can use a binary-search to find the position where to insert a new entry.
   Move all entries with higher indices one position to the right and insert the new index (or if the
   column index exists already, just modify the value).
4. Update the `offset` vector by increasing the number of column values by one (or leave it untouched if the
   existing value was just modified)
5. On `compress()` all three vectors should be transformed into the final format. Therefore traverse
   row-wise, accumulate the row-sizes to get the offset, and collect only those entries in `indices` and `values`
   that are stored in each row.

### Resources

- [Wikipedia:Compressed_Row_Storage](https://de.wikipedia.org/wiki/Compressed_Row_Storage)
- [cppreference:vector](https://en.cppreference.com/w/cpp/container/vector)
- Binary search: [cppreference:lower_bound](https://en.cppreference.com/w/cpp/algorithm/lower_bound). Either pass the pointer to the beginning of the range you want to search, or use `first=indices.begin()+n` (where `n` is the corresponding shift) for the starting point and `last=first+offset[row]` for the end point.
- Insertion algorithms for sparse CRS matrices: http://old.simunova.com/system/files/mtl4_fenics.pdf

### Submission

This exercise can be submitted for review. Please follow the general instructions given in the [README.md](/README.md)
page. In summary: 1. create a new branch `<zih-id>/exercise5`, 2. inside the folder `exercise5/` add
your solution: `task4.cc`, 3. `git add` and `git commit` your added and changed files, 4. push your
branch to the remote repository by `git push origin <zih-id>/exercise5`, 5. create a merge request.

### Pair Review

This time, the review will be done differently. After all submissions are received, you get assigned as reviewer to another submission. We have shown how to do a review in the past exercises. Now it's your turn. Details follow on the next exercise sheet.

**Deadline for the submission: end of 2021/06/09**


## Extra Task 5 (GotW-1: Variable initialization -- or is it?)
See [GotW #1](https://herbsutter.com/2013/05/09/gotw-1-solution/).

What is the difference, if any, among the following?
```c++
widget w;                   // (a)

widget w();                 // (b)
widget w{};                 // (c)

widget w(x);                // (d)
widget w{x};                // (e)

widget w = x;               // (f)
widget w = {x};             // (g)

auto w = x;                 // (h)
auto w = widget{x};         // (i)
```
(`widged` is a class with a default constructor and a single argument constructor that accepts an object `x`.)
