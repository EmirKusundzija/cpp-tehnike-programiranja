#include <iostream>

int main() {

  std::cout << "Unesite znak: ";
  char znak = std::cin.get();
  std::cout << "Znak " << znak << " ima ASCII sifru: " << int(znak) << "\n";
  std::cout << "Znakovi prije znaka " << znak << ": ";

  for (int i = int(znak); i >= 0; i--) {
    std::cout << char(i) << " ";
  }
  std::cout << "\n";

  for (int i = int(znak); i < 127; i++) {
    std::cout << char(i) << " ";
  }
  std::cout << "\n";

  return 0;
}