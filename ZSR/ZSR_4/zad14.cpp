#include <iostream>

bool PozitivniNegativniElementiNiza(double niz[], int br_elemenata, int &poz,
                                    int &neg) {
  poz = 0;
  neg = 0;
  bool element_nula = false;
  for (int i = 0; i < br_elemenata; i++) {
    if (niz[i] < 0) {
      neg++;
    } else if (niz[i] > 0)
      poz++;
    else
      element_nula = true;
  }
  return element_nula;
}

int main() {

  double niz[] = {3, -4, 7.5, -1.1, 5};
  int pozitivni, negativni;
  bool test = PozitivniNegativniElementiNiza(niz, 5, pozitivni, negativni);
  std::cout << "Poz: " << pozitivni << "\nNeg: " << negativni << "\n";
  return 0;
}