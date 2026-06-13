#include <iostream>

int x = 1;

struct A {
  void f() { x *= 2; }
  virtual void g() { x++; }
};
struct B : public A {
  void f() { x -= 3; }
  void g() { x += 2; }
};

void f(A a) {
  a.f();
  a.g();
  x += 5;
}

void g(A &a) {
  a.f();
  a.g();
  x -= 5;
}

int main() {
  A a;
  B b;
  f(a);           // x=8
  f(b);           // x=22
  g(a);           // x =40
  g(b);           // x=77
  std::cout << x; // stanje x-a je 77
  return 0;
}