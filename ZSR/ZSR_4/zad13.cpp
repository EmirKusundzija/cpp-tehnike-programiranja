#include <iostream>

void RazdvojiCifre(int n, int &n_parne_cifre, int &n_neparne_cifre) {
  if (n < 0)
    n = -n;
  int temp = n;

  while (temp > 0) {
    int cifra = temp % 10;
    temp /= 10;
    if (cifra % 2 == 0)
  }
}

int main() {
  int broj_od_parnih, broj_od_neparnih;

  RazdvojiCifre(32564719, broj_od_parnih, broj_od_neparnih);

  std::cout << broj_od_parnih << " " << broj_od_neparnih << "\n";

  return 0;
}