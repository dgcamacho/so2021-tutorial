template<typename T> void bar1()
{ std::cout << "bar1\n"; }

void bar3() { bar1<double>(); }