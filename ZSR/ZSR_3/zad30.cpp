#include <iostream>

int main() {
  int broj;
  std::cout << "Unesite neki broj: ";
  std::cin >> broj;

  std::cout << "Znak koji ima ASCII sifru " << broj
            << " je znak: " << char(broj) << ".\n";
  return 0;
}