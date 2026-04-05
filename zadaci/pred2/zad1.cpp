#include <complex>
#include <iostream>

int main() {

  int n;
  std::cout << "Unesite broj elemenata: ";
  std::cin >> n;
  std::complex<double> z, suma;
  for (int i = 1; i <= n; i++) {
    std::cout << "Z_" << i << " = ";
    std::cin >> z;
    suma += 1. / z;
  }
  std::complex<double> z_total = 1. / suma;
  std::cout << "Paralelna veza ovih elemenata ima impedansu Z_ = " << z_total
            << ".";
  return 0;
}