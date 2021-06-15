template<> void A<double>::foo()
{ std::cout << "foo-double\n"; }

template<typename T> void bar2()
{ std::cout << "bar2\n"; }

int main() {
  A<float> a;
  a.foo();
  bar1<float>();
  bar1<double>();
  bar2<double>();
  bar3();
}