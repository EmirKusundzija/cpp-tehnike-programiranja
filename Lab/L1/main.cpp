#include <iostream>

int main() {
  int a = 0;
  std::cout << "Unesite a: ";
  if (!(std::cin >> a) || a <= 0 || a > 99999) {
    std::cout << "Niste unijeli broj, vozdra\n";
    return 1;
  }
  int b = 0;
  std::cout << "Unesite b: ";
  if (!(std::cin >> b) || b <= 0 || b > 99999) {
    std::cout << "Niste unijeli broj, vozdra\n";
    return 1;
  }

  for (int i = a; i <= b; i++) {
    int temp = i;
    int suma = 0;
    while (temp > 0) {
      int cifra = temp % 10;
      suma += cifra;
      temp /= 10;
    }
    if (i % suma == 0)
      std::cout << i << "\n";
  }
  return 0;
}