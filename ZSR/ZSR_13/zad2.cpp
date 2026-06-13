#include <iostream>
struct A {
  int X() { return 3; }
  virtual int Y() { return 5; }
};
struct B : public A {
  int X() { return 1; }
  int Y() { return 7; }
};

struct C {
  int x, y;
  C(int x, int y) : x(x), y(y) {}
};

std::ostream &operator<<(std::ostream &t, C c) {
  return t << "{" << c.x << "," << c.y << "}";
}

C P(A x) { return {x.X(), x.Y()}; }
C Q(A &y) { return C(y.X(), y.Y()); }

int main() {
  A x;
  B y;
  std::cout << P(x) << " " << P(y) << " " << Q(x) << " " << Q(y);

  // P(x) = {3,5}
  // P(y) = {3,5}
  // Q(x) = {3,5}
  // Q(y) = {3,7}
  return 0;
}