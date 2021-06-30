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


## Task 2 (Inheritance and Functions)
Find the errors in the following program. What is the output after the incorrect lines are removed,
and why?
```c++
#include <iostream>

class SuperClass
{
private:
  void foo () const
  {
    std::cout << "SuperClass::foo" << std::endl;
  }
};

class DerivedClass : public SuperClass
{
public:
  void foo ()
  {
    std::cout << "DerivedClass::foo" << std::endl;
  }
};

class LeafClass : private DerivedClass
{
protected:
  void bar ()
  {
    foo();
  }
};

void test (SuperClass const& super)
{
  super.foo();
}

int main ()
{
  SuperClass super;
  DerivedClass derived;
  LeafClass leaf;

  super.foo();

  derived.foo();
  test(derived);

  leaf.bar();
  test(leaf);
}
```


## Task 3 (Iterators)
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


## Task 4 (Functor composition)
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



## Extra Task 5 (GotW-2: Temporaries)
See [GotW #2](https://herbsutter.com/2013/05/13/gotw-2-solution-temporary-objects/).

1. What is a temporary object?

2. You are doing a code review. A programmer has written the following function, which uses unnecessary temporary or extra objects in at least three places. How many can you identify, and how should the programmer fix them?

```c++
std::string find_addr (std::list<employee> emps, std::string name) {
  for (auto i = std::begin(emps); i != std::end(emps); i++) {
    if( *i == name ) {
      return i->addr;
    }
  }
  return "";
}
```

Do not change the operational semantics of this function, even though they could be improved.