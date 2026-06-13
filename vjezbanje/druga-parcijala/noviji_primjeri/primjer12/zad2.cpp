#include <iostream>

class A {
public:
  virtual int P() const { return 5; }
};
class B : public A {
public:
  int P() const { return 8; }
};

int P(A a) { return 3 * a.P(); }
int Q(const A &a) { return a.P() + 5; }

int main() {
  std::cout << P(A()) << " " << P(B()) << " " << Q(A()) << " " << Q(B());
  // P(A()) 3*5 = 15
  // P(B()) 3*5 = 15
  // Q(A()) 5+5=10
  // Q(B()) 5+8 = 13
}