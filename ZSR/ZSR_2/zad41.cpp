#include <cmath>
#include <iostream>
#include <vector>

bool JeArmstrongovBroj(int n) {
  int br = 0;
  int temp = n;
  while (temp > 0) {
    temp /= 10;
    br++;
  }
  temp = n;
  int suma = 0;
  while (temp > 0) {
    int cifra = temp % 10;
    suma += std::pow(cifra, br);
    temp /= 10;
  }

  return suma == n;
}
std::vector<int> ArmstrongovBrojevi(int p, int q) {
  std::vector<int> temp;
  for (int i = p; i <= q; i++) {
    if (JeArmstrongovBroj(i))
      temp.push_back(i);
  }
  return temp;
}

int main() {
  int p, q;

  std::cout << "Unesite p i q: ";
  std::cin >> p >> q;
  std::vector<int> brojevi = ArmstrongovBrojevi(p, q);

  if (brojevi.empty()) {
    std::cout << "Nema Armstrongovih brojeva u traženom opsegu";
  } else {

    std::cout << "Armstrongovi brojevi u rasponu [" << p << "," << q << "]: ";

    for (int i = 0; i < brojevi.size(); i++) {
      std::cout << brojevi.at(i);
      if (i != brojevi.size() - 1)
        std::cout << ", ";
    }
  }
  return 0;
}