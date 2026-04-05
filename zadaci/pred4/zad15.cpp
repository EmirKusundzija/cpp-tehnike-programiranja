#include <iostream>
#include <string_view>

template <typename TipBroja>
void UnosBroja(std::string_view prompt, std::string_view warning,
               TipBroja &broj) {

  for (;;) {
    std::cout << prompt;
    if ((std::cin >> broj) && std::cin.peek() == '\n')
      return;
    std::cout << warning;
    std::cin.clear();
    std::cin.ignore(10000, '\n');
  }
}

int main() {
  double broj;
  UnosBroja("Unesite bazu: ", "Neispravan unos, pokusajte ponovo...\n", broj);
  std::cout << "\n";
  int eksp;
  UnosBroja("Unesite cjelobrojni eksponent: ",
            "Neispravan unos, pokusajte ponovo...\n", eksp);
  double stepen = 1;

  if (eksp > 0) {
    for (int i = 1; i <= eksp; i++)
      stepen *= broj;
  } else {
    for (int i = 1; i <= -eksp; i++)
      stepen /= broj;
  }

  std::cout << broj << " na " << eksp << " iznosi " << stepen << "\n";
  return 0;
}