#include <iostream>

struct X {
  int i;
  
  // constructor
  X(int i_) : i(i_)
  { 
    std::cout << "X::X(int)\n"; 
  }
  
  // X + int
  X operator+(int j) const
  { 
    std::cout << "X::operator+(int)\n"; 
    return {i+j}; 
  }
};

struct Y {
  int i;
  
  // constructor
  Y(X x) : i(x.i)
  { 
    std::cout << "Y::Y(X)\n"; 
  }           
  
  // Y + X
  Y operator+(X x) const
  { 
    std::cout << "Y::operator+(X)\n"; 
    return {X(i+x.i)}; 
  }
  
  // cast-to-int operator
  operator int() const
  { 
    std::cout << "Y::operator int()\n"; 
    return i; 
  }
};

inline X operator*(X x,Y y) // X * Y
{ 
  std::cout << "operator*(X,Y)\n"; 
  return {x.i * y.i}; 
}

inline int f(X x) // f(X) -> int
{ 
  std::cout << "f(X)\n"; 
  return x.i; 
}

int main() {
  X x = 1;
  Y y = x;
  int i = 2;

       
  
  // adding two integers, no conversion necessary
  std::cout << "EXPRESSION(i + 10):\n";
  i + 10;
  
  // either y->int or int(10)->X
  std::cout << "EXPRESSION(y + 10): does not compile\n";
  /*y + 10;*/
  
  // either y->int or int(10)->X
  std::cout << "EXPRESSION(y + 10 * y): does not compile\n";
  /*y + 10 * y;*/
  
  // 1. y is converted to int -> yi
  // 2. x + yi (result needs conversion of int to X) -> xy
  // 3. xy + i (result needs conversion of int to X)
  std::cout << "EXPRESSION(x + y + i):\n";
  x + y + i;  
  
  // 1. second x is converted to Y -> xY
  // 2. x * xY (result needs conversion of int to X) -> xx
  // 3. xx + i (result needs conversion of int to X)
  std::cout << "EXPRESSION(x * x + i):\n";
  x * x + i;
  
  // 1. 7 is converted to X -> X7
  // 2. f(X7)
  std::cout << "EXPRESSION(f(7)):\n";
  f(7);
  
  // y can not be converted to X
  std::cout << "EXPRESSION(f(y)): does not compile\n";
  /*f(y);*/
  
  // 1. both y are converted to int -> yi
  // 2. yi + yi
  std::cout << "EXPRESSION(y + y):\n";
  y + y;      
  
  // 1. y is converted to int -> yi
  // 106 + yi
  std::cout << "EXPRESSION(106 + y):\n";
  106 + y;
}
