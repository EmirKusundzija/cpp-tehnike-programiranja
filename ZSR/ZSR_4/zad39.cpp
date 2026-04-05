#include <iostream>
#include <string>
void DodajRazmak(std::string &s, int n) {
  std::string rez = "";
  for (int i = 0; i < s.length(); i++) {
    rez += s.at(i);
    rez += std::string(n, ' ');
  }
  s = rez;
}

int main() {
  std::string testni_string;

  std::cout << "Unesite recenicu: ";
  std::getline(std::cin, testni_string);
  DodajRazmak(testni_string, 1);

  std::cout << testni_string << "\n";

  return 0;
}