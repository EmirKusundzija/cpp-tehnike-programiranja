// TP 2025/2026: Zadaća 1, Zadatak 1
#include <array>
#include <iostream>
#include <stdexcept>
#include <vector>

enum class TretmanNegativnih { IgnorirajZnak, Odbaci, PrijaviGresku };

long long int MultiplikativniDigitalniKorijen(long long int broj,

                                              int baza_broja) {
  long long int temp = broj;
  if (temp < 0)
    temp = -temp;
  if (!(baza_broja >= 2))
    throw std::domain_error("Neispravna baza");

  while (temp >= baza_broja) {
    long long int p = 1;
    while (temp > 0) {
      int cifra = temp % baza_broja;
      p *= cifra;
      temp /= baza_broja;
    }
    temp = p;
  }

  return temp;
}

std::array<std::vector<long long int>, 10>
RazvrstajBrojeve(std::vector<long long int> brojevi,
                 TretmanNegativnih tretman) {

  std::array<std::vector<long long int>, 10> rezultat;

  for (int i = 0; i < brojevi.size(); i++) {
    long long int broj = brojevi.at(i);

    if (broj < 0) {
      if (tretman == TretmanNegativnih::IgnorirajZnak)
        broj = -broj;
      else if (tretman == TretmanNegativnih::Odbaci)
        continue;
      else
        throw std::domain_error(
            "Nije predvidjeno razvrstavanje negativnih brojeva");
    }

    int korijen = MultiplikativniDigitalniKorijen(broj, 10);
    rezultat.at(korijen).push_back(brojevi.at(i));
  }
  return rezultat;
}

int main() {
  try {
    std::vector<long long int> brojevi;
    std::cout << "Unesite brojeve (bilo koji ne-broj oznacava kraj): ";
    long long int broj;
    bool ima_negativnih_brojeva = false;
    while (std::cin >> broj) {
      if (broj < 0)
        ima_negativnih_brojeva = true;
      brojevi.push_back(broj);
    }

    if (ima_negativnih_brojeva) {
      std::cout << "Nije podrzano razvrstavanje negativnih brojeva!\n";
      return 0;
    }

    auto rezultat = RazvrstajBrojeve(brojevi, TretmanNegativnih::IgnorirajZnak);

    std::cout
        << "Rezultati razvrstavanja po multiplikativnom digitalnom korijenu:\n";

    for (int i = 0; i < 10; i++) {
      if (rezultat.at(i).size() == 0)
        continue;

      std::cout << i << ": ";
      for (int j = 0; j < rezultat.at(i).size(); j++) {
        std::cout << rezultat.at(i).at(j) << " ";
      }
      std::cout << "\n";
    }

  } catch (std::domain_error izuzetak) {
    std::cout << "GRESKA: " << izuzetak.what() << "!\n";
  }

  return 0;
}
