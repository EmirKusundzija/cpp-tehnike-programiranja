#include <iostream>

int Cifre(long long int n, int &c_min, int &c_max) {
  long long int temp = n;
  int br = 0;
  c_min = 9;
  c_max = 0;
  if (temp < 0)
    temp = -temp;
  while (temp > 0) {
    int cifra = temp % 10;
    temp /= 10;
    br++;

    if (cifra > c_max)
      c_max = cifra;
    if (cifra < c_min)
      c_min = cifra;
  }
  return br;
}

int main() {
  int broj;
  std::cout << "Unesite broj: ";
  std::cin >> broj;
  int min_cifra, max_cifra;
  int poziv = Cifre(broj, min_cifra, max_cifra);
  std::cout << "Min: " << min_cifra << "\nMax: " << max_cifra << "\n";
  return 0;
}