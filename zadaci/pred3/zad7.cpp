#include <iostream>
#include <stdexcept>
#include <string>

std::string IzdvojiRijec(std::string s, int poz_rijeci) {
  int duzina = s.length();
  int brojac = 0;
  for (int i = 0; i < duzina; i++) {
    if (s[i] != ' ' && (i == 0 || s[i - 1] == ' ')) {
      brojac++;
    }
    if (brojac == poz_rijeci) {
      std::string rijec;
      while (s[i] != ' ' && i < duzina)
        rijec += s[i++];
      return rijec;
    }
  }
  throw std::range_error("Pogresan redni broj rijeci!");
}

int main() {
  int n;
  try {
    std::cout << "Unesite redni broj rijeci: ";
    std::cin >> n;
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    std::string recenica;
    std::cout << "Unesite recenicu: ";
    std::getline(std::cin, recenica);
    std::cout << "Rijec na poziciji " << n << " je "
              << IzdvojiRijec(recenica, n) << "\n";
  } catch (std::domain_error e) {
    std::cout << "IZUZETAK: " << e.what();
  }
  return 0;
}