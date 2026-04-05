#include <cmath>
#include <iostream>
#include <vector>

bool ElementiSaPotpunimKvadratima(std::vector<int> v) {
  for (int i = 0; i < v.size(); i++) {
    int korijen = std::sqrt(v.at(i));
    if (korijen * korijen == v.at(i))
      return true;
  }
  return false;
}

int main() {

  int n;
  std::cout << "Unesite n: ";
  std::cin >> n;
  std::vector<int> elementi;

  for (int i = 0; i < n; i++) {
    int broj;
    std::cin >> broj;
    elementi.push_back(broj);
  }
  if (ElementiSaPotpunimKvadratima(elementi))
    std::cout << "Ima elemenata sa potpunim kvadratima!\n";
  else
    std::cout << "Nema elemenata sa potpunim kvadratima!\n";

  return 0;
}