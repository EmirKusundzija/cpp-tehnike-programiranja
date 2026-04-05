#include <iostream>
#include <stdexcept>
#include <vector>

double F(std::vector<double> v) {

  double suma = 0.0;
  double rez = 0.0;
  for (int i = 0; i < v.size(); i++) {
    suma += v.at(i);
    if (suma == 0)
      throw std::domain_error("Dijeljenje sa 0 nema smisla konju jedan!\n");
    rez += 1. / suma;
  }
  return rez;
}

int main() {

  try {
    int n;
    std::cout << "Unesite n: ";
    std::cin >> n;
    std::vector<double> brojevi;

    for (int i = 0; i < n; i++) {
      double broj;
      std::cout << "Unesite element: ";
      std::cin >> broj;
      brojevi.push_back(broj);
    }

    std::cout << "Rezultat: " << F(brojevi) << "\n";
  } catch (std::domain_error e) {
    std::cout << "Greska: " << e.what();
  } catch (...) {
    std::cout << "Nepoznata greska!\n";
  }

  return 0;
}