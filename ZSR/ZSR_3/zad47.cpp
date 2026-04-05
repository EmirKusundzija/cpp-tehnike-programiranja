#include <iostream>
#include <string>

std::string RijecSaZnakom(std::string s, char c) {

  for (int i = 0; i < s.length(); i++) {
    if (s.at(i) == ' ')
      std::cout << c;
    else
      std::cout << s.at(i);
  }
  return s;
}

int main() {

  //   std::string recenica;
  //   std::cout << "Unesite recenicu: ";
  //   std::getline(std::cin, recenica);

  std::string testiranje{"Danas je ispit iz TP-a"};
  std::cout << "Nova recenica: " << RijecSaZnakom(testiranje, ',');
}