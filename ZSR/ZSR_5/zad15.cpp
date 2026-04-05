#include <iostream>

template <typename Pok>
int BrojTrocifrenihBrojeva(Pok *pocetak, Pok *nakon_kraja) {
  int brojac = 0; // nemamo trocifrene brojeve
  while (pocetak != nakon_kraja) {
    if (*pocetak >= 100 && *pocetak <= 999)
      brojac++;
    pocetak++;
  }
  return brojac;
}

int main() {
  int niz[5]{2, 5, 600, 19};

  int rezulat_fje = BrojTrocifrenihBrojeva(niz, niz + 5);

  std::cout << rezulat_fje << " " << "\n";
}