#include <iostream>
#include <string>

int main() {
  std::string s1, s2;
  std::cout << "Unesite recenicu 1:";
  std::getline(std::cin, s1);

  std::cout << "Unesite recenicu 2:";
  std::getline(std::cin, s2);

  int br1 = 0, br2 = 0;
  for (int i = 0; i < s1.length(); i++) {
    br1++;
  }
  for (int i = 0; i < s2.length(); i++) {
    br2++;
  }
  std::cout << "Recenica 1 ima " << br1 << " znakova!\nRecenica 2 ima " << br2
            << " znakova!\n";
  std::string s3 = s1 + s2;
  if (s1.at(0) < s2.at(0))
    std::cout << "Recenica 1 dolazi prije 2!\n";
  else
    std::cout << "Recenica 2 dolazi prije 1!\n";
  std::cout << "Nova recenica sastavljena od rec. 1 i rec. 2: " << s3 << "\n";
  std::cout << "Recenica 1 u obrnutom poretku: ";
  for (int i = s1.length() - 1; i >= 0; i--)
    std::cout << s1.at(i);
  std::cout << "\n";
  return 0;
}