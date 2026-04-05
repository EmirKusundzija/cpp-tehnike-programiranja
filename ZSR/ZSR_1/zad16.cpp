#include <iostream>

int MultiOptornost(int n) {
  if (n >= 1 && n <= 9)
    return 0;

  int br = 0;
  while (n >= 10) {
    int p = 1;
    while (n > 0) {

      int cifra = n % 10;
      p *= cifra;
      n /= 10;
    }
    n = p;
    br++;
  }
  return br;
}

int main() {
  int a, b, k;
  std::cout << "Unesite a, b i k: ";
  std::cin >> a >> b >> k;

  for (int i = a; i <= b; i++) {
    if (MultiOptornost(i) == k)
      std::cout << i << " ";
  }

  return 0;
}