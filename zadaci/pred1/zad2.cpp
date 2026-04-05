#include <cmath>
#include <iomanip>
#include <iostream>
int main() {
  int a, b;
  std::cout << "Unesite pocetnu i krajnju vrijednost: ";
  std::cin >> a >> b;

  std::cout << "\n"
            << "+---------+----------+----------+-----------+\n"
            << "| Brojevi | Kvadrati | Korijeni | Logaritmi |\n"
            << "+---------+----------+----------+-----------+\n";
  for (int i = a; i <= b; i++) {
    std::cout << "| " << std::left << std::setw(8) << i << "|" << std::right
              << std::setw(9) << i * i << " |" << std::fixed << std::setw(9)
              << std::setprecision(3) << std::sqrt(i) << " |" << std::setw(10)
              << std::setprecision(5) << std::log(i) << " |\n";
  }
  std::cout << "+---------+----------+----------+-----------+\n";

  return 0;
}