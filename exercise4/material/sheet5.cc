# include <iostream>

// struct X {
//   int i;
//   X(int j) : i(j) {
//     std::cout << "X constructed from int\n";
//   } // constructor
//   X operator+(int j) { // X + int
//     std::cout << "X added to int\n";
//     X res = X(i + j);
//     return res;
//   }
// };

// struct Y {
//   int i;
//   Y(X x) : i(x.i) { // constructor
//     // i = x.i;
//     std::cout << "Y constructed from X\n";
//   }
//   Y operator+(X x) { // Y + X
//     std::cout << "Y + X called\n";
//     Y res = Y((x + this->i));
//     return res;
//   }
//   operator int() { // cast-to-int operator
//     std::cout << "Y cast to int\n";
//     return this->i;
//   }
// };

// inline X operator*(X x,Y y) {
//     X res = X(x.i * y.i);
//     std::cout << "X * Y done\n";
//     return res;
// } // X * Y
// inline int f(X) {
//     std::cout << "f called\n";
//     return 0;
// }; // f(X) -> int

// int main() {
//   X x = 1;
//   Y y = x;
//   int i = 2;

//   std::cout << i + 10 << '\n'; // int + int, no conversion
//   // std::cout << y + 10 << '\n'; // probably: Y cast to int, int addition. Actually: ambiguous
//   // std::cout << y + 10 * y << '\n'; // probably: Y cast to int, int*; Y cast to int, int+. Actually: ambiguous
//   std::cout << (x + y + i).i << '\n'; // Y cast to int, X+int; X+int
//   std::cout << (x * x + i).i << '\n'; // X constructor to Y, X*Y -> Y; Y cast to int, int+
//   std::cout << f(7) << '\n'; // int constructor to X; call
//   // std::cout << f(y) << '\n'; // uncallable, will not cast and construct implicitly
//   std::cout << y + y << '\n'; // Both Y cast to int, int+
//   std::cout << 106 + y << '\n'; // Y cast to int, int+
// }


// void foo(int a) {std::cout << "a\n"; };            // (a)
// void foo(int& a) {std::cout << "b\n"; };           // (b)
// void foo(int* a) {std::cout << "c\n"; };           // (c)
// void foo(double a) {std::cout << "d\n"; };         // (d)
// void bar(int a, int b) {std::cout << "e\n"; };     // (e)
// void bar(float a, float b) {std::cout << "f\n"; }; // (f)
// // template <class T, class U>
// // void bar(T a, U b) {};

// int main() {
//   int a = 1;
//   float b = 1.0f;
//   double c = 1.0;

//   // foo(a);       // (1) // ambiguous
//   foo(&a);      // (2) // (c)
//   foo(1.0);     // (3) // (d)
//   foo(b);       // (4) // cast to double + call (d)
//   foo((int*)&b);      // (5) // does not exist, can we manually force this?
//   foo(c);       // (6) // (d)

//   bar(a, a);    // (7) // (e)
//   bar(1.0, a);  // (8) // (e)
//   // bar(&a, a);   // (9) // ???
//   bar(b, b);    // (10)// (f)
//   // bar(c, c);    // (11)// ambiguous
//   bar(b, c);    // (12)// (f)
//   // bar(a, b);    // (13)// ambiguous
// }

# include <typeinfo>
class widget
{
    public:
        int i;    
};

class doodad
{
};

class gadget {};

int main() {
    widget w{1};
    std::cout << w.i;
}
