#include <iostream>
class A {
  int x, y;

public:
  A() {
    std::cout << "A\n";
    x = 1;
    y = 2;
  }
  A(int x, int y) {
    std::cout << "B\n";
    A::x = x;
    A::y = y;
  }
  void w(int z) {
    x *= z;
    y *= z;
  }
  int u() { return x + 10; }
  int v() { return y - 5; }
  void s() { std::cout << x + y << " " << x - y << std::endl; }
};
class B {
  int x;
  A y;

public:
  B(int y) {
    std::cout << "C\n";
    x = y;
  }
  B(int x, int y, int z) : y(x, z) {
    std::cout << "D\n";
    B::x = y;
  }
  int u() { return x; }
  A v() { return y; }
  void s() {
    std::cout << x << std::endl;
    y.s();
  }
};
int main() {
  A a;       // ispisuje A i postavlja x,y -> 1,2 (to je default konstruktor)
  A b(3, 2); // Ispisuje B i postavlja x,y -> 3,2
  std::cout << a.u() << " " << a.v() << std::endl; // 11 -3
  std::cout << b.u() << " " << b.v() << std::endl; // 13 -3
  a.s();                                           // 3 -1
  b.s();                                           // 5 1
  A c = a;                                         //
  c.w(2);
  a.s();
  c.s();
  B d(2);
  B e(1, 5, 3);
  std::cout << d.u() << " " << d.v().u() << " " << d.v().v() << std::endl;
  e.s();
  A f[4];
  A g[3] = {{3, 2}, {1, 1}, {2, 2}};
  f[2].s();
  g[1].s();
  A *p, *q;
  p = new A(10, 10);
  q = p;
  q->w(3);
  p->s();
  return 0;
}