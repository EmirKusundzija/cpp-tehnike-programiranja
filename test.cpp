#include <iostream>

template <typename T>
bool VecBrojan(T niz1[], int n1, T element, int do_indeksa) {
  for (int i = 0; i < do_indeksa; i++)
    if (niz1[i] == element)
      return true;
  return false;
}

template <typename T> int BrojZajednickih(T niz1[], int n1, T niz2[], int n2) {
  int brojac = 0;
  for (int i = 0; i < n1; i++) {
    if (VecBrojan(niz1, n1, niz1[i], i))
      continue; // duplikat u niz1, preskoči
    for (int j = 0; j < n2; j++) {
      if (niz1[i] == niz2[j]) {
        brojac++;
        break;
      }
    }
  }
  return brojac;
}

int main() {
  int a[8] = {3, 7, 2, 3, 1, 5, 5, 2};
  int b[10] = {4, 6, 7, 8, 1, 3, 1, 6, 4, 7};
  std::cout << BrojZajednickih(a, 8, b, 10) << "\n"; // 3
  return 0;
}