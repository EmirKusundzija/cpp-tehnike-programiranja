#include <cmath>
#include <complex>
#include <iostream>

// using namespace std::complex_literals;

int main() {
  std::complex<double> z;
  std::cout << "Unesite z = ";
  std::cin >> z;
  double x, y;
  std::cout << "Unesite x i y: ";
  std::cin >> x >> y;

  std::complex<double> razlomak =
      std::complex<double>(0, 5) /
      ((z * z * z) * std::sqrt(std::complex<double>(x, -y)));

  std::complex<double> izraz = (x + razlomak);

  std::complex<double> rezultat = izraz * izraz;

  std::cout << "Rez = " << rezultat;
}