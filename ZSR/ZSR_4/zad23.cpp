#include <iostream>

bool ParniNeparniElementi(int niz[], int br_elemenata, int &parno,
                          int &neparno) {
  parno = 0;
  neparno = 0;
  bool element_manji_od0 = false;
  for (int i = 0; i < br_elemenata; i++) {
    if (niz[i] < 0)
      element_manji_od0 = true;
    if (niz[i] % 2 == 0)
      parno++;
    else
      neparno++;
  }
  return element_manji_od0;
}

int main() {
  int niz[5]{3, 4, 6, 7, 9};
  int parno, neparno;
  bool poziv = ParniNeparniElementi(niz, 5, parno, neparno);
  std::cout << "Br. parnih elemenata: " << parno << "\n";
  std::cout << "Br. neparnih elemanata: " << neparno << "\n";

  if (poziv) {
    std::cout << "Ima negativnih elemenata!\n";
  } else
    std::cout << "Nema negativnih elemenata!\n";

  return 0;
}