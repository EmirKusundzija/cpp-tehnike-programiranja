#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

int main() {

  std::vector<std::list<int>> elementi{{1, 2, 3}, {2, 3, -5}};

  std::sort(elementi.begin(), elementi.end(),
            [](std::list<int> &a, std::list<int> &b) {
              int suma1 = 0;
              for (auto &x : a) {
                suma1 += x;
              }
              int suma2 = 0;
              for (auto &x : b) {
                suma2 += x;
              }
              return suma1 < suma2;
            });

  for (auto &x : elementi) {
    for (auto &element : x) {
      std::cout << element << " ";
    }
    std::cout << "\n";
  }

  return 0;
}