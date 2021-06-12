# Exercise sheet 6 (June 9th 2021)

## Task 1 (Vector class)
In the following vector class and main function there are more than 25 programming
and style errors included. Try to find as many as possible.
```c++
class vector
{
  typedef value double;

  vector(int s)
    : s(s), data(new double[s])

  vector(vector const& that)
    : s(that.s), data(new double[s])
  {
    for (int i= 0; i <= s; i++)
      that.data[i] = data[i];
    return *this;
  }

  ~vector(double[] data) { delete data; }

  vector& operator= (vector const& that) const {
    assert(s != that.s)
    for (unsigned i= s-1; i >= 0; i--)
      data[i]= that.data[i];
    return this;
  }

  double const& operator[](unsigned i)
  {
    return data(i);
  }

  double& operator[]( unsigned i )
  {
  return data(i);
  }

  unsigned size(const vector& v) { return v->s; }

private:
  double const data[];
  unsigned const s;
}

void main()
{
  vector v1(6);
  vector v2(v1);
  vector v3(10);
  v1 = v2;
  v3 = v2;
  v1(2) = 1;
  const vector v4(v2);
  v4[2] = 1.0;
  v4.size(v3);
}
```


## Task 2 (Pointers)
Let `i` have the type `int`, and `p` the type `int *`. Which of the following
expressions are correct, which are incorrect? Also list the types of the correct
ones. Answer without taking concrete values for `i` and `p` into account.

```c++
i + 1       &p            p[i]          ++p
*p          p + 1         *(p + i)      p++
*p + 3      &p == i       *(i + p)      *p++
&i == p     **(&p)        *(p - i)      *++p
i == *p     *p + i > i    *(p*i)        (*p)++
```


## Task 3 (Templates)
We have a header file `task3.hh` that declares a class and three methods:

```c++
template<typename T> struct A { void foo(); };
template<typename T> void bar1();
template<typename T> void bar2();
void bar3();
```

In another header file `task3.impl.hh` we provide the definition of the member-function of the class-template:

```c++
template<typename T>
void A<T>::foo() { std::cout << "foo-T\n"; }
```

In a third file `task3.cc` we provide the implementation of two methods:

```c++
template<typename T> void bar1() { std::cout << "bar1\n"; }
void bar3() { bar1<double>(); }
```

and finally in the main `task3_main.cc` file we have

```c++
template<> void A<double>::foo() { std::cout << "foo-double\n"; }
template<typename T> void bar2() { std::cout << "bar2\n"; }
int main() {...}
```

1. Try to find the links between these file. Which files needs to include which else. Finally we want to compile
both `.cc` files via

```
> c++ task3.cc task3_main.cc -o task3
```

2. Consider the following implementation of the `main()` function:

```c++
int main()
{
  A<float> a;
  a.foo();
  bar1<float>();
  bar1<double>();
  bar2<double>();
  bar3();
}
```
Try to compile the code. What error do you get and why? Try to remove the corrupted line and compile again! What is the output of the program and why? Use the tools `nm` or `objdump` in order to find the provided and expected symbols in the files.


## Task 4 (Test of CRSMatrix)
Test the implementation of the `CRSMatrix` class by creating the following matrix and vector:

```math
    A = \begin{pmatrix}
      2 & -1 & 0\\
      -1 & 2 & -1\\
      0 & -1 & 2
    \end{pmatrix},\quad
    x =
    \begin{pmatrix}
    1\\
    1\\
    1
    \end{pmatrix}.
```
Compute the matrix-vector product `A * x` and compare with the exact result.


## Extra Task 5 (GotW-30: Koenig Lookup)
See [GotW #30](http://www.gotw.ca/gotw/030.htm).

Recapitulation Name Lookup: In the following code, which functions are called? Why? Analyze the implications.
```c++
namespace A {
  struct X;
  struct Y;
  void f(int); // (a)
  void g(X);   // (b)
}

namespace B {
  void f(int i) {  // (c)
    f(i);   // which f()?
  }
  void g(A::X x) { // (d)
    g(x);   // which g()?
  }
  void h(A::Y y) { // (e)
    h(y);   // which h()?
  }
}
```

### Resources
- Koenig Lookup or [Argument dependent name lookup](https://de.wikipedia.org/wiki/Argument_dependent_name_lookup)
