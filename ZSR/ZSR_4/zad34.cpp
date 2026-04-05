#include <iostream>
#include <string>

void ASCIIUmanjenZaN(std::string &s, int n) {
  for (int i = 0; i < s.length(); i++) {
    s.at(i) -= n;
  }
}

int main() {
  std::string test;
  int n;
  std::getline(std::cin, test);
  std::cin >> n;
  std::cout << "Originalni string: " << test << "\n";
  ASCIIUmanjenZaN(test, n);
  std::cout << "String pri cemu je ASCII sifra umanjena za (" << n
            << "): " << test;

  return 0;
}