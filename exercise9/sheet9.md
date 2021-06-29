# Exercise sheet 9 (June 30th 2021)

## Task 1 (Valgrind)

1. Create a small program that creates arrays on the heap (using dynamic allocation). Therefore, write a function `int allocate(int n)`
   that calls itself recursively with decreasing `n` and allocates for each `n > 0` an array of integers of size `n`. The return value of that function
   is `0` in this exercise. Do not call `delete` explicitly. In your `main()`, call this function for some moderate `n`, compile your code and run it.

2. In each recursive call of `allocate()`, return the entry `n-1` of the array plus the value of the recursively called `allocate()`.
   In case of `n==0` just return `0`, i.e., in python pseudo-code:

```python
def allocate(n):
  if n == 0:
    return 0

  # - allocate array a with size n
  # - recursively call allocate
  m = allocate(n - 1)
  return a[n-1] + m
```
  In your `main()`, print the number received from the `allocate()` call. Compile and run again.

3. Instead of accessing the `n-1`th element, read from the `n`th element in the return statement of the `allocate()` function. Compile and run again!


All these three steps contain memory-related errors. Here they are obvious, but in other cases it might be hard to see it from just looking at the code.
Therefore, there are tools that help finding the errors. One such tool, we have already tried out: *GDB*. Another tool that we want to look at is
*Valgrind*.

The *Valgrind* tool suite provides a number of debugging and profiling tools that help you make your programs faster and more correct.
The most popular of these tools is called *Memcheck*. It can detect many memory-related errors that are common in C and C++ programs
and that can lead to crashes and unpredictable behavior.

### Usage of Valgrind
If you normally run your program like this:
```bash
> ./myprog arg1 arg2
```
Use the following command instead:
```
> valgrind [OPTIONS] ./myprog arg1 arg2
```
Memcheck is the default tool. As options you may use `--leak-check=full` to turns on the detailed memory leak detector,
or `--track-origins=yes` to see where uninitialized values come from, or another option.

### References
- [Valgrind](http://valgrind.org/docs/manual/quick-start.html)


## Task 2 (Iterators)
In *python* operations on ranges are a fundamental concept and make the language very nice to use. An
example is the `map` operation, that takes a range and applies a functor to each element, when traversing the
range:
```python
for x in map(lambda x: 2*x, range(0,10)):
  print(x)
```
Here, an integer range `[0, 10)` is created and the entries are scaled by a factor 2, but only during iteration in
the loop. We want to implement something similar in C++:
- take a functor and a range,
- provide iterators over the range and
- return on dereferencing the mapped value

Therefore, write a class `MappedRange<Functor,Range>` with a constructor that stores a functor, gets a range
and stores iterators to begin and end of the range:
```c++
MappedRange(Functor f, Range const& range)
  : f_(f)
  , it_(range.begin())
  , end_(range.end())
{}
```
What are the types of the stored iterators? Then, implement a class `MappedIterator` that contains `operator++`,
`operator==`, and `operator!=` implemented in terms of the original range iterators! Finally, implement a new
dereferencing operation `operator*`, by returning the mapped dereferenced range iterator.
```c++
auto operator*() const {
  return f_(*it_);
}
```
This `MappedIterator` needs the functor and a range iterator to work with. Write member-functions `begin()`
and `end()` in the class `MappedRange` that return a `MappedIterator`.

To create an instance of the class `MappedRange` write a generator function, i.e., a function template that just instantiates
the class:
```c++
template <class Functor, class Range>
MappedRange<Functor, Range> map(Functor f, Range const& range)
{
  /* implementation here */
}
```
Try out your implementation with a vector and a list filled with some values, or with the integer-range
from exercise sheet 9.


## Task 3 (Functor composition)
If you have functors that represent some mathematical functions like `sqr`, `sqrt`, `exp`, `tanh`,... how could you combine these functors in order to build more complex operations. Mathematically spoken: let $`f : A \to B`$ and $`g : B \to C`$ be two unary functors with `argument_types` $`A`$ and $`B`$, and `return_types` $`B`$ and $`C`$ respectively. Build a functor `Composer` that implements the composition $`f \circ g : A \to C, x \mapsto g(f(x))`$.

In order to do so, write a class `Composer` first that takes two constructor arguments representing the functors for $`f`$ and $`g`$ and provide a free function that instantiates this class:
```c++
template <class F, class G>
class Composer
{
public:
  Composer(F const& f, G const& g) : (...) { ... }

  result_type operator()(argument_type const& x) const { ... }
private:
  // ...
};

template <class F, class G>
Composer<F,G> compose(F const& f, G const& g) { // generator-function
  return Composer<F,G>(f,g);
}
```
Fill in the missing parts and specify `argument_type` and `result_type`.

(optional) Write the composer class, using C++-Lambda expressions instead. See also
[CppTruths](http://cpptruths.blogspot.de/2014/03/fun-with-lambdas-c14-style-part-1.html) for possible
solutions.

### Note
- Instead of providing a *generator*-function to instantiate the class, you could rely on class-template-argument deduction of c++17.

### Resources
- [cppreference:class_template_argument_deduction](https://en.cppreference.com/w/cpp/language/class_template_argument_deduction)


## Task 4 (Smart Pointers)
Consider the following code:
```c++
#include <memory>
std::shared_ptr<int> create_int_ptr(int value)
{
  return std::shared_ptr<int>( new int{value} );
  // or: return make_shared<int>(value);
}

int main()
{
  std::shared_ptr<int> i;
  {
    std::shared_ptr<int> j = create_int_ptr(2);
    i = j;
  }
  // #1
  return 0;
}
```
- Is this a valid program, or are there *dangling* pointer?
- How many pointers point to the memory of the allocated integer when reaching line `#1`?
- Can you replace `shared_ptr` by `unique_ptr` in this code? Why (not)?


## Extra Task 5 (GotW-89: Smart Pointers)
See [GotW #89](https://herbsutter.com/2013/05/29/gotw-89-solution-smart-pointers).

1. When should you use `shared_ptr` vs. `unique_ptr`? List as many considerations as you can.
2. (Guru) Why should you almost always use `make_shared` to create an object to be owned by `shared_ptr`s? Explain.
3. (Guru) Why should you almost always use `make_unique` to create an object to be initially owned by a `unique_ptr`? Explain.

## Extra Task 6 (GotW-91: Smart Pointer Parameters)
Also interesting: Passing smart pointers to functions? See [GotW #91](https://herbsutter.com/2013/06/05/gotw-91-solution-smart-pointer-parameters)