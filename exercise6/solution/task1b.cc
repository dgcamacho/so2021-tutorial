#include "Vector.hh" // Move implementation to separate header file

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