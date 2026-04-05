#include <iostream>

void SumeCifara(int n, int &s_par, int &s_nepar) {
  int temp = n;
  s_par = 0;
  s_nepar = 0;
  while (temp > 0) {
    int cifra = temp % 10;
    temp /= 10;
    if (cifra % 2 == 0)
      s_par += cifra;
    else
      s_nepar += cifra;
  }
}

int main() {

  for (;;) {

    int broj;
    std::cout << "Unesite broj: ";
    std::cin >> broj;
    if (broj == 0)
      break;
    int a, b;

    SumeCifara(broj, a, b);

    std::cout << "Parno: " << a << "\nNeparno: " << b << "\n";
  }
}