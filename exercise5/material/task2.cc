#include <iostream>

using std::cout; using std::endl;

void foo(int a) {std::cout << "a)" << std::endl;}            // (a)
void foo(int& a) {std::cout << "b)" << endl;}        // (b)
void foo(int* a) {cout << "c)" << endl;}       // (c)
void foo(float a) {cout << "d)" <<endl;}         // (d)
void bar(int a, int b) {cout << "e) " << endl;}    // (e)
void bar(float a, float b) {cout << "f)" << endl;} // (f)

int main() {
  int a = 1;
  float b = 1.0f;
  double c = 1.0;

  //foo(a);       // (1) ?
  foo(&a);      // (2)
  foo(1.0);     // (3)
  foo(b);       // (4)
  //foo(&b);      // (5)
  foo(c);       // (6)
/*
  bar(a, a);    // (7)
  bar(1.0, a);  // (8)

  //bar(&a, a);   // (9)
  bar(b, b);    // (10)
  //bar(c, c);    // (11)
  bar(b, c);    // (12)
  bar(a, b);    // (13)
  */
}

