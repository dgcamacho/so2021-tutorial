#include <type_traits>

int main()
{
  int i;    // integer type
  int* p;   // pointer to integer type

  static_assert(std::is_same<decltype(i + 1), int>::value, "");       // increment of an integer
  static_assert(std::is_same<decltype(&p), int**>::value, "");        // address of the pointer variable: pointer to pointer to int
  static_assert(std::is_same<decltype(*p), int&>::value, "");         // dereference the pointer, get the data it points to as reference
  static_assert(std::is_same<decltype(**(&p)), int&>::value, "");     // &p => int**, two-time dereferencing gives int reference
  static_assert(std::is_same<decltype(p + 1), int*>::value, "");      // pointer arithmetic, move one position forward
  static_assert(std::is_same<decltype(*p + 3), int>::value, "");      // dereference -> int, plus int => int
  // static_assert(std::is_same<decltype(&p == i), bool>::value, "");    // ERROR: pointer cannot be compared to integer type!
  static_assert(std::is_same<decltype(&i == p), bool>::value, "");    // two pointers of the same type can be compared
  static_assert(std::is_same<decltype(i == *p), bool>::value, "");    // Comparison of two integers is fine
  static_assert(std::is_same<decltype(*p + i > i), bool>::value, ""); // Comparison of two integers is fine

  static_assert(std::is_same<decltype(p[i]), int&>::value, "");  // equivalent to *(p + i)
  static_assert(std::is_same<decltype(*(p+i)), int&>::value, "");  // equivalent to p[i]
  static_assert(std::is_same<decltype(*(i+p)), int&>::value, "");  // equivalent to p[i]
  static_assert(std::is_same<decltype(*(p-i)), int&>::value, "");  // move pointer i positions backward and then dereference
  // static_assert(std::is_same<decltype(*(p*i)), int&>::value, ""); // ERROR
  static_assert(std::is_same<decltype(++p), int*&>::value, "");
  static_assert(std::is_same<decltype(p++), int*>::value, "");
  static_assert(std::is_same<decltype(*p++), int&>::value, "");  // return the dereferenced pointer p before it is incremented
  static_assert(std::is_same<decltype(*++p), int&>::value, "");   // First increment the pointer then dereference
  static_assert(std::is_same<decltype((*p)++), int>::value, ""); // increment the integer that is obtained by dereferencing the pointer
}