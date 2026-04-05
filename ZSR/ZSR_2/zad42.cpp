#include <iostream>
#include <vector>
int ObrnutIspisCifre(int n) {
  int obrnuto = 0;
  int predznak = n < 0 ? -1 : 1;
  if (n < 0)
    n = -n;
  while (n > 0) {
    int cifra = n % 10;
    n /= 10;
    obrnuto = obrnuto * 10 + cifra;
  }
  return obrnuto * predznak;
}

std::vector<int> SlikeUOgledalu(std::vector<int> brojevi) {
  std::vector<int> temp;
  for (int i : brojevi) {
    temp.push_back(ObrnutIspisCifre(i));
  }
  return temp;
}

int main() {

  std::vector<int> test;
  int broj;

  while (std::cin >> broj && broj != 0)
    test.push_back(broj);

  std::vector<int> fja = SlikeUOgledalu(test);

  for (int i = 0; i < fja.size(); i++) {
    std::cout << "Slika u ogledalu broja " << test.at(i) << " glasi "
              << fja.at(i) << ".\n";
  }

  return 0;
}