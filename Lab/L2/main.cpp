#include <iostream>
#include <vector>

bool ImaCetverocifrenih(std::vector<int> v) {
  for (auto x : v) {
    if (x >= 1000 && x <= 9000)
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
    std::cout << "Unesite " << i + 1 << ". element: ";
    std::cin >> broj;
    brojevi.push_back(broj);
  }

  if (ImaCetverocifrenih(brojevi)) {
    std::cout << "Ima cetverocifrenih brojeva!\n";
  } else
    std::cout << "Nema cetverocifrenih brojeva!";
  return 0;
}