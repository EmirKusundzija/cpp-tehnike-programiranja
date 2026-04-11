// TP 2025/2026: Zadaća 2, Zadatak 2
#include <cmath>
#include <iostream>
#include <stdexcept>

// n = a^2+b^2+c^2+d^2
void SumaCetiriKvadrata(int n, int &a, int &b, int &c, int &d) {
  if (n < 0)
    throw std::domain_error("Broj koji se rastavlja mora biti nenegativan");
  for (a = std::sqrt(n); a >= 0; a--) {
    for (b = a; b >= 0; b--) {
      for (c = b; c >= 0; c--) {
        int ostatak = n - a * a - b * b - c * c;
        if (ostatak < 0)
          continue;

        d = std::sqrt(ostatak);

        if (a * a + b * b + c * c + d * d == n && c >= d)
          return;
      }
    }
  }
}

int main() {

  int n;
  std::cout << "Unesite prirodan broj: ";

  if (!(std::cin >> n) || n < 0) {
    std::cout << "Uneseni broj nije prirodan broj!\n";
    return 0;
  }

  int a, b, c, d;

  SumaCetiriKvadrata(n, a, b, c, d);

  std::cout << n << "=" << a << "^2+" << b << "^2+" << c << "^2+" << d
            << "^2\n";

  return 0;
}
