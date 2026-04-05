#include <iostream>
#include <string>

int BrojRijeci(std::string s) {
  int br = 0;

  for (int i = 0; i < s.length(); i++) {
    if (s.at(i) != ' ' && (i == 0 || s.at(i - 1) == ' '))
      br++;
  }
  return br;
}

int main() {

  std::string recenica;
  std::cout << "Unesite recenicu: ";
  std::getline(std::cin, recenica);

  std::cout << "Broj rijeci u recenici: " << BrojRijeci(recenica) << "\n";
}