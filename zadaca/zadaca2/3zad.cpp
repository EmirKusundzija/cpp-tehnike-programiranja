// TP 2025/2026: Zadaća 2, Zadatak 3
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

template <typename F, typename A, typename B>
auto GeneraliziraniSpoljasnjiProizvod(A kontejner1, B kontejner2, F f)
    -> std::vector<std::vector<decltype(f(*std::begin(kontejner1),
                                          *std::begin(kontejner2)))>> {

  using Tip = decltype(f(*std::begin(kontejner1), *std::begin(kontejner2)));

  std::vector<std::vector<Tip>> matrica;

  auto it1 = std::begin(kontejner1), kraj1 = std::end(kontejner1);
  auto it2 = std::begin(kontejner2), kraj2 = std::end(kontejner2);

  if (it1 == kraj1 || it2 == kraj2)
    return matrica;

  while (it1 != kraj1) {
    std::vector<Tip> red;
    it2 = std::begin(kontejner2);
    while (it2 != kraj2) {
      red.push_back(f(*it1, *it2));
      it2++;
    }
    matrica.push_back(red);
    it1++;
  }

  return matrica;
}

int main() {
  int n;
  std::cout << "Unesite broj elemenata prve sekvence: ";
  std::cin >> n;

  std::vector<std::string> A(n);

  std::cout << "Unesite elemente prve sekvence: ";
  for (auto &x : A) {
    std::cin >> x;
  }

  int m;
  std::cout << "Unesite broj elemenata druge sekvence: ";
  std::cin >> m;

  std::vector<std::string> B(m);

  std::cout << "Unesite elemente druge sekvence: ";
  for (auto &x : B) {
    std::cin >> x;
  }

  auto rezultat = GeneraliziraniSpoljasnjiProizvod(
      A, B,
      [](const std::string &s1, const std::string &s2) { return s1 + s2; });

  int sirina = 0;

  for (auto &red : rezultat) {
    for (auto &element : red) {
      if (element.length() > sirina)
        sirina = element.length();
    }
  }
  std::cout << "\n";
  for (auto &red : rezultat) {
    for (auto &element : red) {
      std::cout << std::left << std::setw(sirina + 1) << element;
    }
    std::cout << "\n";
  }

  return 0;
}
