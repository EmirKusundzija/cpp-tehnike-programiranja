#include <complex>
#include <iostream>

int main() {

  int n;
  std::cout << "Unesite broj elemenata: ";
  std::cin >> n;
  std::complex<double> suma;
  for (int i = 1; i <= n; i++) {
    double R, X;
    std::cout << "R" << i << " = ";
    std::cin >> R;
    std::cout << "X" << i << " = ";
    std::cin >> X;
    std::cout << "\n";
    std::complex<double> z(R, X);
    suma += 1. / z;
  }
  std::complex<double> z_total = 1. / suma;
  std::cout << "Paralelna veza ovih elemenata ima R = " << std::real(z_total)
            << " i X = " << std::imag(z_total) << ".";
  return 0;
}