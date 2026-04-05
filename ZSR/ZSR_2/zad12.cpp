#include <iostream>
#include <vector>

bool ImaTrocifrenihBrojeva(std::vector<int> v) {
  for (int i = 0; i < v.size(); i++) {
    if (v.at(i) >= 100 && v.at(i) <= 999)
      return true;
  }
  return false;
}

int main() {
  int n;
  std::cout << "Unesite n: ";
  std::cin >> n;

  std::vector<int> brojevi;
  for (int i = 0; i < n; i++) {
    int broj;
    std::cout << "Unesite " << i + 1 << ". broj: ";
    std::cin >> broj;
    brojevi.push_back(broj);
  }

  if (ImaTrocifrenihBrojeva(brojevi)) {
    std::cout << "Ima trocifrenih brojeva!\n";
  } else
    std::cout << "Nema trocifrenih brojeva!\n";
  return 0;
}