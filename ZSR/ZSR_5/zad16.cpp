#include <iostream>

template <typename Pok> int BrojParnihBrojeva(Pok *pocetak, Pok *nakon_kraja) {
  int brojac = 0; // nemamo parne brojeve
  while (pocetak != nakon_kraja) {
    if (*pocetak % 2 == 0)
      brojac++;
    pocetak++;
  }
  return brojac;
}

int main() {
  int niz[5]{2, 5, 600, 19, 27};

  int rezulat_fje = BrojParnihBrojeva(niz, niz + 5);

  std::cout << rezulat_fje << " " << "\n";
}