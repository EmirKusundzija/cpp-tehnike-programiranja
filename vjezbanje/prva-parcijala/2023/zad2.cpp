// TP 2022/2023 Zadatak 2

#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

int main() {
  std::vector<std::list<int>> vektor_listi{{1, 2, 3}, {-1, 2}};

  std::cout << "Originalni elementi vektora: ";
  std::cout << "\n";
  for (auto &x : vektor_listi) {
    for (auto &element : x) {
      std::cout << element << " ";
    }
    std::cout << "\n";
  }

  std::sort(vektor_listi.begin(), vektor_listi.end(),
            [](std::list<int> lista1, std::list<int> lista2) {
              int suma1 = 0;
              for (auto &x : lista1) {
                suma1 += x;
              }
              int suma2 = 0;
              for (auto &x : lista2) {
                suma2 += x;
              }
              return suma1 < suma2;
            });

  std::cout << "Sortirana lista (po sumama u rastucem redoslijedu): \n";
  for (auto &x : vektor_listi) {
    for (auto &element : x) {
      std::cout << element << " ";
    }
    std::cout << "\n";
  }

  return 0;
}