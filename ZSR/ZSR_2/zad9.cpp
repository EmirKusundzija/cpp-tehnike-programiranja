#include <iostream>
#include <vector>

bool ParniElementi(std::vector<int> brojevi) {
  for (int i = 0; i < brojevi.size(); i++) {
    if (brojevi.at(i) % 2 == 0)
      return true;
  }
  return false;
}

int main() {
  int n;
  std::cout << "Unesite n: ";
  std::cin >> n;

  std::vector<int> v;

  for (int i = 0; i < n; i++) {
    int broj;
    std::cout << "Unesite " << i + 1 << ". broj: ";
    std::cin >> broj;
    v.push_back(broj);
  }

  if (ParniElementi(v)) {
    std::cout << "Ima parnih elemenata!\n";
  } else
    std::cout << "Nema parnih elemenata!\n";
  return 0;
}