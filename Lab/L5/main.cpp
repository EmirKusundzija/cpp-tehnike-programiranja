#include <iostream>
#include <string>
#include <vector>

template <typename IterTip, typename SmislenTip>
int Prebroji(IterTip p1, IterTip p2,
             SmislenTip f) { // moze se deducirati kao pokazivac na funkciju
                             // SmislentTip (*f)(parametri)
  int br = 0;

  while (p1 != p2) {
    if (f(*p1)) {
      br++;
    }
    p1++;
  }
  return br;
}

int main() {
  // Testiranje 1
  int n;

  std::cout << "Unesite n: ";
  std::cin >> n;

  std::vector<int> a(n);

  for (auto &x : a) {
    std::cin >> x;
  }

  int broj_cetverocifrenih = Prebroji(a.begin(), a.end(), [](int element) {
    return element >= 1000 && element <= 9999; // [1000,9999]
  });

  std::cout << "Broj cetverocifrenih elemenata u vektoru: "
            << broj_cetverocifrenih << "\n";
  // Testiranje 2
  int k;

  std::cout << "Unesite broj stringova: ";
  std::cin >> k;
  // ciscenje nakon unosa (jer se moze pokupiti \n)
  std::cin.clear();
  std::cin.ignore(10000, '\n');

  std::vector<std::string> stringovi(k);

  for (auto &x : stringovi) {
    std::getline(std::cin, x);
  }

  int broj_razlicitih_od_sest =
      Prebroji(stringovi.begin(), stringovi.end(), [](const std::string &s) {
        char pronadjeni[256] = {};
        int razliciti = 0;
        for (int i = 0; i < s.size(); i++) {
          char c = s.at(i);
          if (!pronadjeni[c]) {
            pronadjeni[c] = 1;
            razliciti++;
          }
        }
        return razliciti > 6;
      });

  std::cout << "Broj elemenata u vektoru s vise od 6 razlicitih karaktera: "
            << broj_razlicitih_od_sest << "\n";

  return 0;
}