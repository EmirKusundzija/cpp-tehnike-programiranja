#include <complex>
#include <iomanip>
#include <iostream>

void F1(int a, int b) {
  a = b + 3;
  b = a - 1;
  std::cout << a << b;
}
void F2(int &a, int &b) {
  a = b + 3;
  b = a - 1;
  std::cout << a << b;
}
int *F3(int a, int *b) {
  std::cout << (*b)++; // 6+1 (mijenjali smo x kod F2 koja je imala reference a
                       // i b na x )
  return new int(a);
}
int main() {
  int x(4);
  std::complex<double> c(4), i(0, 1);
  std::cout << std::setw(5) << c * c << c * i << std::setw(9) << c * i - c
            << std::endl;      // (16,0)(0,4)   (-4,4)
  F1(x, x);                    // 7 6
  std::cout << x << std::endl; // 4
  F2(x, x);                    // 6 6
  std::cout << x << std::endl; // 6
  *F3(x, &x) =
      7; // nije uradjen delete nakon dinamicke alokacije i moze biti UB
  std::cout << x << std::endl;
  return 0;
}