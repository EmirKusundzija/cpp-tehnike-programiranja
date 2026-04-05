#include <iostream>
#include <vector>

bool DaLiJeProst(int n) {
  if (n < 2 || n != 2 && n % 2 == 0)
    return false;
  for (int i = 3; i <= n / i; i += 2)
    if (n % i == 0)
      return false;
  return true;
}

std::vector<int> ProstiBrojeviUOpsegu(int a, int b) {
  std::vector<int> v;
  for (int i = a; i <= b; i++) {
    if (DaLiJeProst(i))
      v.push_back(i);
    if (i == b)
      break;
  }
  return v;
}
int main() {

  int pocetak, kraj;
  std::cout << "Unesite pocetnu i krajnju vrijednost: ";
  std::cin >> pocetak >> kraj;
  std::vector<int> brojevi;

  auto v = ProstiBrojeviUOpsegu(pocetak, kraj);
  if (v.size() == 0)
    std::cout << "Nema prostih brojeva u rasponu od " << pocetak << " do "
              << kraj << "!\n";
  else {
    std::cout << "Prosti brojevi u rasponu od " << pocetak << " do " << kraj
              << " su: ";
    for (int i = 0; i < v.size(); i++)
      std::cout << v.at(i) << (i != v.size() - 1 ? ", " : "\n");
  }

  return 0;
}