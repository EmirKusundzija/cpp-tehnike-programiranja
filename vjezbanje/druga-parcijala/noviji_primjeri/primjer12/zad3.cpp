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

int main() {}