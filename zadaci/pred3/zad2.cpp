#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>
int BinomniKoeficijent(int i, int j) {
  int p = 1;
  for (int k = 1; k <= j; k++)
    p = p * (i + 1 - k) / k;
  return p;
}

std::vector<std::vector<int>> PaskalovTrougao(int n) {
  if (n < 0)
    throw std::domain_error("Broj redova ne smije biti negativan");
  std::vector<std::vector<int>> a(n);
  for (int i = 0; i < n; i++) {
    a.at(i).resize(i + 1);
    a.at(i).at(0) = 1;
    a.at(i).at(i) = 1;
    for (int j = 1; j < i; j++)
      a.at(i).at(j) = a.at(i - 1).at(j) + a.at(i - 1).at(j - 1);
  }
  return a;
}

int NajvecaSirina(std::vector<std::vector<int>> m) {
  int najveci = 0;
  for (auto red : m) {
    for (int x : red) {
      int brojac = x <= 0;
      for (; x != 0; x /= 10)
        brojac++;
      if (brojac > najveci)
        najveci = brojac;
    }
  }
  return najveci;
}

int main() {
  int n;
  std::cout << "Unesite broj redova: ";
  std::cin >> n;
  auto a = PaskalovTrougao(n);
  int sirina = NajvecaSirina(a) + 1;
  std::cout << std::endl;
  for (auto red : a) {
    for (int x : red)
      std::cout << std::setw(sirina) << x;
    std::cout << std::endl;
  }
  return 0;
}