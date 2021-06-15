#include <cassert>                                // (1) needs include for assert
#include <cstddef>                                // (2) needs additional include for std::size_t

class Vector                                      // (3) classes in upper case
{
public:                                           // (4) member functions and some type should be public
  typedef double value_type;                      // (5) wrong order in typedef
  typedef std::size_t size_type;                  // (6) introduce type of size and indices

  explicit Vector (size_type size = 0)            // (7),(8),(9), (10) type should match member variable type, name must be meaningful, default constructor, single-argument constructor should be marked `explicit`
    : size_(size)                                 // (11) member variable with different name than parameter
    , data_(size_ > 0 ? new value_type[size_] : nullptr)   // (12),(13),(14) member variable with common style, test for 0-size arrays, use typedef for value type
  {}

  Vector (Vector const& that)
    : Vector{that.size_}                          // (15) Call other constructor for initialization
  {
    for (size_type i = 0; i < size_; ++i)         // (16),(17),(18) size_type, upper limit of loop, ++i
      data_[i] = that.data_[i];                   // (19) copy from that to this
  }                                               // (20) no return statement in constructor!

  ~Vector () { delete[] data_; }                  // (21),(22) destructor without arguments, delete must match new

  Vector& operator= (Vector const& that)          // (23),(24) assignment operator is non-const, use common bracket-style
  {
    assert(size_ == that.size_);                  // (25) inverse logic in assert, end statement with a ";"
    if (this != &that) {                          // (26) no self-assignment!
      for (size_type i = 0; i < size_; ++i)       // (27) loop index is always >= 0, thus infinite loop
        data_[i] = that.data_[i];
    }
    return *this;                                 // (28) return reference, not pointer
  }

                                                  // (29),(30) missing move constructor, move-assignment operator (see later)

  value_type const& operator[] (size_type i) const// (31),(32), types and const-access function must be marked const
  {
    return data_[i];                              // (33) access to data with square brackets
  }

  value_type& operator[] (size_type i)            // same as above
  {
    return data_[i];
  }

  size_type size () const { return size_; }       // (34) size() should be a member function not a free function, also no vector argument

private:
  size_type const size_;                          // (35) order of the member variables
  value_type* data_;                              // (36) static array without size not possible as class member, but raw pointer
};                                                // (37) class closes with semicolon;

int main ()                                       // (38) main() must return integer
{
  Vector v1(6);
  Vector v2(v1);
  Vector v3(10);
  v1 = v2;
  //v3 = v2;                                      // (39) assignment of vectors of different size
  v1[2] = 1;                                      // (40) wrong access operator
  const Vector v4(v2);
  //v4[2] = 1.0;                                  // (41) assignment to const object not allowed
  v4.size();                                      // (42) wrong syntax for call to size()
}