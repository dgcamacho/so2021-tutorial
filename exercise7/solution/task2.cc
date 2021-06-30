#include <cassert>
#include <vector>

namespace scprog
{
  // Returns true if the range [first1, last1) is equal to the range [first2, first2 + (last1 - first1)), and false otherwise
  template <class InputIt1, class InputIt2>
  bool equal (InputIt1 first1, InputIt1 last1, InputIt2 first2)
  {
    for (; first1 != last1; ++first1, ++first2) {
      if (!(*first1 == *first2)) {
        return false;
      }
    }
    return true;
  }

  /*
  // equal algorithm with concepts
  template <std::input_iterator I1, std::sentinel_for<I1> S1,
            std::input_iterator I2, std::sentinel_for<I2> S2>
    requires std::indirectly_comparable<I1, I2>
  bool equal (I1 first1, S1 last1, I2 first2, S2 last2);
  */


} // end namespace scprog

int main()
{
  std::vector<int> v1{1,2,3,4,5,6,7};
  std::vector<int> v2{2,3,4,5,6,7,8};

  assert(!scprog::equal(v1.begin(), v1.end(), v2.begin()));
  assert( scprog::equal(v1.begin(), v1.end(), v1.begin()));
}
