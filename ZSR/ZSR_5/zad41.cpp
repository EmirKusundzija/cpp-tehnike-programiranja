#include <algorithm>
#include <complex>
#include <iostream>

bool Kriterij(std::complex<double> z1, std::complex<double> z2) {
  if (std::imag(z1) < std::imag(z2) ||
      (std::imag(z1) == std::imag(z2) && std::real(z1) < std::real(z2)))
    return true;
  return false;
}

int main() {
  int n;
  std::cout << "Unesite velicinu niza: ";
  std::cin >> n;

  std::complex<double> niz[100];

  for (int i = 0; i < n; i++) {
    std::cout << "Unesite " << i + 1 << ". kompleksni broj: ";
    std::cin >> niz[i];
  }

  std::sort(niz, niz + n, Kriterij);

  std::cout << "Brojevi sortirani po kriteriju: ";
  for (int i = 0; i < n; i++) {
    std::cout << niz[i] << " ";
  }
  std::cout << "\n";
  return 0;
}
