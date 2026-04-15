// TP 2025/2026: Zadaća 2, Zadatak 2
#include <cmath>
#include <iostream>
#include <stdexcept>

bool PotpunKvadrat(int x) {
  if (x < 0)
    return false;
  int r = std::sqrt(x);
  return (long long)r * r == x; // r*r moze prekoraciti opseg tipa int
}

// n = a^2+b^2+c^2+d^2
void SumaCetiriKvadrata(int n, int &a, int &b, int &c, int &d) {
  if (n < 0)
    throw std::domain_error("Broj koji se rastavlja mora biti nenegativan");

  // pamcenje posljednjeg rezultata
  static bool zapamcen = false;
  static int N, A, B, C, D;

  if (zapamcen && n == N) {
    a = A;
    b = B;
    c = C;
    d = D;
    return;
  }

  int korijen = std::sqrt(n);

  for (a = korijen; a >= 0; a--) {
    int ostatak1 = n - a * a;

    int x = ostatak1;
    while (x > 0 && x % 4 == 0)
      x /= 4;
    if (x % 8 == 7)
      continue;

    int gornja_granica_b = std::sqrt(ostatak1);
    if (gornja_granica_b > a)
      gornja_granica_b = a;

    for (b = gornja_granica_b; b >= 0; b--) {
      int ostatak2 = ostatak1 - b * b;
      int gornja_granica_c = std::sqrt(ostatak2);
      if (gornja_granica_c > b)
        gornja_granica_c = b;

      for (c = gornja_granica_c; c >= 0; c--) {
        int ostatak3 = ostatak2 - c * c;
        if (!PotpunKvadrat(ostatak3))
          continue;

        d = std::sqrt(ostatak3);

        if (d <= c) {
          zapamcen = true;
          N = n;
          A = a;
          B = b;
          C = c;
          D = d;
          return;
        }
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
