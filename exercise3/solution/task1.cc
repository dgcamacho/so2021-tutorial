#include <iostream>

// This is a macro, i.e., a simple parametrized string replacement, that
// 1. resets the values of the variables to its original value
// 2. prints the value of the expression
// 3. prints the value of the variables after evaluating the expression
#define EVAL(CHAR, EXPR) x=3; y=2; z=5; print("(" #CHAR ")", EXPR); print("x=",x,"y=",y,"z=",z)

void print() { std::cout << std::endl; }

// This is a simple print function printing all its arguments to std::cout finalized with a std::endl
template <class T0, class... T>
void print(T0 const& arg0, T const&... args) {
  std::cout << arg0 << ' ';
  print(args...);
}

int main()
{
  int x = 3, y = 2, z = 5;

  EVAL(a, (x / y) * z);
  EVAL(b, (x * (y++)) / (-z));
  EVAL(c, (x^(2 + y))^2);
  EVAL(d, (++x) * (x++)); // PROBLEM: order of evaluation!
  EVAL(e, ((*(&x))*y)&&z);
  EVAL(f, (x++)+x);

  EVAL(g, ((z-y)-x)?((x+y)+z):((x-y)-z));
  EVAL(h, (z<<x)>>y);
  EVAL(i, (z>>x)<<y);
  EVAL(j, x||(y|z));
  EVAL(k, (++x)*=(y++));
  EVAL(l, (-(~x))^x);
}