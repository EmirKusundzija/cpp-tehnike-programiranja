#include <iostream>
int c = 5;
struct A {
  int x;
  A(int x = 1) : x(x) {}
  int operator[](int x) { return x + 2; }
  int operator[](int x) const { return x * 2; }
  int operator()() { return x - 1; }
  int operator()() const { return x * 3; }
  int operator()(int x) { return 2 - x; }
  int operator()(int x) const { return x + 3; }
};
struct B : public A {
  int y;
  B() : y(x + c) { c++; }
};
int main() {
  A a(3); // x=3
  B b[5]; // inicijalizira 5 objekata tipa B
  for (auto x : b)
    std::cout << x.y
              << " "; // prva iteracija 6, druga 7 pa sve do zadnjeg pa bude 10
  std::cout << std::endl
            << a[3] << " " << A()[3] << " " << a(3) << " " << A(3)(3) << " "
            << A(A()[3])() << " " << A(a[3])() << " " << a(a[3]);
  return 0;
}