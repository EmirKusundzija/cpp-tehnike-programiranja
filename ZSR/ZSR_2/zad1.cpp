#include <iostream>

bool SimetricanBroj(int n) {
  int broj = n;
  int broj_obrnut = 0;
  while (n > 0) {
    int cifra = n % 10;
    n /= 10;

    broj_obrnut = broj_obrnut * 10 + cifra;
  }

  return broj == broj_obrnut;
}

int main() {
  int broj;

  while (std::cin >> broj && broj != 0) {
    if (SimetricanBroj(broj))
      std::cout << "Broj je simetrican.\n";
    else
      std::cout << "Broj nije simetrican!\n";
  }

  return 0;
}