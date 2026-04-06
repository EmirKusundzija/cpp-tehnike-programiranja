#include <iostream>
#include <string>

std::string RijecBezRazmaka(std::string &s, char znak) {
  std::string rezultat;
  int i = 0;
  int duzina = s.length();

  while (i < duzina && s.at(i) == ' ')
    i++;

  while (i < duzina) {
    while (i < duzina && s.at(i) != ' ') {
      rezultat += s.at(i);
      i++;
    }
    while (i < duzina && s.at(i) == ' ')
      i++;

    if (i < duzina)
      rezultat += znak;
  }
  return rezultat;
}

int main() {
  std::string recenica;
  std::cout << "Unesite recenicu: ";
  std::getline(std::cin, recenica);
  std::cout << "Unesite znak kojim zelite zamijeniti razmake: ";
  char umjesto_razmaka = std::cin.get();
  std::string test = RijecBezRazmaka(recenica, umjesto_razmaka);
  std::cout << "Modificirana recenica: ";
  std::cout << test << "\n";
  return 0;
}