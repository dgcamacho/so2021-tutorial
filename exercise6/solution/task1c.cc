#include <vector>

namespace scprog
{
  // Implementation by deriving from the class std::vector
  class Vector
      : public std::vector<double>
  {
    using Super = std::vector<double>;

  public:
    // use names similar to std containers
    using value_type = double;
    using size_type = std::vector<double>::size_type;

    // default constructor, just allocates memory, no initialization!
    explicit Vector (size_type const size = 0)
      : Super(size)
    {}

    // Constructor that initializes all components with value
    Vector (size_type const size, value_type const value)
      : Super(size, value)
    {}
  };

} // end namespace scprog

int main()
{
  using namespace scprog;

  Vector v1(6);
  Vector v2(v1);
  Vector v3(10);
  v1 = v2;
  v1[2] = 1;
  const Vector v4(v2);
  v4.size();
}