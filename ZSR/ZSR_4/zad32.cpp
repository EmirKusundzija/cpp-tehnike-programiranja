#include <iostream>
int Sume(int niz[], int br_elemenata, int &parno, int &neparno) {
  parno = 0;
  neparno = 0;

  for (int i = 0; i < br_elemenata; i++) {
    if (niz[i] % 2 == 0)
      parno += niz[i];
    else
      neparno += niz[i];
  }
  return parno - neparno;
}

int main() {
  int n;
  std::cout << "Unesite broj elemenata: ";
  std::cin >> n;

  int a[1000];

  for (int i = 0; i < n; i++)
    std::cin >> a[i];

  int x, y;
  int z = Sume(a, n, x, y);

  std::cout << "Parno: " << x << "\nNeparno: " << y << "\nRazlika: " << z
            << "\n";

  return 0;
}