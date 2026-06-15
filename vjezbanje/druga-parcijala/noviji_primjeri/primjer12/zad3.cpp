#include <iostream>
class P {
  int x;

public:
  P(int x) : x(x) {}
  void f() { std::cout << x << " "; }
  virtual void g() { std::cout << -x << " "; }
};
class Q : public P {
  int y;

public:
  Q(int x, int y) : P(x), y(y) {}
  void f() { std::cout << y << " "; }
  void g() { std::cout << -y << " "; }
};

int main() {
  P a(1);
  Q b(2, 3);
  P *c = new P(4);
  P *d = new Q(5, 6);
  Q *e = new Q(7, 8);
  a.f();  // 1
  a.g();  // -1
  b.f();  // 3
  b.g();  // -3
  c->f(); // 4
  c->g(); // -4
  d->f(); // 5
  d->g(); // -6
  e->f(); // 8
  e->g(); // -8
}