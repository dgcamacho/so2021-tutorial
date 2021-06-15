# Exercise sheet 7 (June 16th 2021)

## Task 1 (Function templates)
(a) Write a function template `minmax(a,b)` to calculate minimum and maximum of two values `a` and
`b` of the same type given as arguments to the function. The return type should be a pair of values, i.e.
`std::pair<T,T>`, where `T` is the type of the arguments. The first entry in the pair corresponds to the minimal
value, the second entry to the maximal value.

What are the requirements on the types that must be fulfilled in order to call the function properly?

**Guru Question:** Could this be implemented using C-Macros? If yes, how? Why are function templates the
better choice?

(b) Consider the generic function
```c++
template <typename T1, typename T2>
T1 min (T1 a, T2 b)
{
  return a < b ? a : b;
}
```
Which design decision are inappropriate? Why? Construct a function call that results in a wrong result!

(c) Templates can be used to specify the functionality in a function, e.g.
```c++
#include <functional> // -> std::less
template <typename T, typename Compare = std::less<T> >
T min (T a, T b, Compare less = Compare{})
{
  return less(a, b) ? a : b;
}
```
How to call that function for values of type `int`, `double`, and for a user-defined type, like `Vector`?
What do you need to implement in order to make the call work?


## Task 2 (Algorithms)
What does the following algorithm implement?
```c++
template <class InputIt1, class InputIt2>
bool ALGORITHM1 (InputIt1 first1, InputIt1 last1, InputIt2 first2)
{
  for (; first1 != last1; ++first1, ++first2) {
    if (!(*first1 == *first2)) {
      return false;
    }
  }
  return true;
}
```
Describe the requirements on the input types.


## Task 3 (Temporaries)
In `material/CGSolver.hh` an implementation of the CG-algorithm is given with a syntax very close to the mathematical notation. A corresponding matrix and vector class is provided. The implementation is not very efficient in terms of handling temporary objects.

1. Write a test program that verifies correctness of the implementation of `CGSolver`, `Vector` and `Matrix` classes. You can use the matrix and vector data from the last exercise sheet.

2. Identify the source of the inefficiency (Note: look at the function declarations). Additionally, quantify the inefficiency, i.e., count how often temporary variables are created, copied and destroyed, during one iteration of the CG method.

3. Modify the function declarations in `Vector.hh` to improve the program. Check that your optimization still produces the correct behavior of the functions and classes. Why are not all inefficiencies solved by this strategy?


## Task 4 (Code Review)
If you have submitted a solution of the exercise sheet 5, you get assigned a peer as reviewer of your
code and you get assigned a review task. Watch notification from GitLab or look into the Merge-Requests
assignment page to be found in the top right corner of the GitLab page. Follow some code review guidelines,
extracted from [Google's Engineering Practice](https://google.github.io/eng-practices/review/)

### Code reviews should look at

- **Design:** Is the code well-designed and appropriate for your system?
- **Functionality:** Does the code behave as the author likely intended? Is the way the code behaves good for its users?
- **Complexity:** Could the code be made simpler? Would another developer be able to easily understand and use this code when they come across it in the future?
- **Tests:** Does the code have correct and well-designed tests?
- **Naming:** Did the developer choose clear names for variables, classes, methods, etc.?
- **Comments:** Are the comments clear and useful?
- **Style:** Does the code follow some consistent code style?
- **Documentation:** Did the developer include relevant documentation?

### How to do code review?

In order to write constructive, effective and respectful code review, some guidelines should be followed.
I hardly recommend to read [Philipp Hauer's Code Review Guidelines for Humans](https://phauer.com/2018/code-review-guidelines)


## Extra Task 5 (GotW-4: Class Mechanics)
See [GotW #4](https://herbsutter.com/2013/05/20/gotw-4-class-mechanics).

1. What makes interfaces "easy to use correctly, hard to use incorrectly"? Explain.
2. You are doing a code review. A programmer has written the following class, which shows some poor style and has some real errors. How many can you find, and how would you fix them?
```c++
class complex {
public:
    complex( double r, double i = 0 )
        : real(r), imag(i)
    { }

    void operator+ ( complex other ) {
        real = real + other.real;
        imag = imag + other.imag;
    }

    void operator<<( ostream os ) {
        os << "(" << real << "," << imag << ")";
    }

    complex operator++() {
        ++real;
        return *this;
    }

    complex operator++( int ) {
        auto temp = *this;
        ++real;
        return temp;
    }

    // ... more functions that complement the above ...

private:
    double real, imag;
};
```

Note: This is not intended to be a complete class. For example, if you provide `operator++` you would normally also provide `operator--`. Rather,
this is an instructive example to focus on the mechanics of writing correctly the kinds of functions this class is trying to support.
