#include <iostream>
#include <string>

int main() {
  std::string recenica;

  std::cout << "Unesite recenicu: ";
  std::getline(std::cin, recenica);
  int start = 0;
  for (int i = 0; i < recenica.length(); i++) {
    if (recenica.at(i) == ' ')
      start = i + 1;
  }
  std::cout << "Posljednja rijec u recenici: ";
  for (int j = start; j < recenica.length(); j++) {
    std::cout << recenica.at(j);
  }

  return 0;
}