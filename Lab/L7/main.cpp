#include <algorithm>
#include <deque>
#include <iostream>
#include <list>

int main() {
  std::deque<std::list<int>> podaci{{3, 1, 4, 2, 5},
                                    {-1, 3, 5, 7, 8},
                                    {3, 4, 5, 6, 7, 100, 29},
                                    {4, 7, -1, -1, -100, 23},
                                    {2, 3, 1},
                                    {-11, 3, 7, 8},
                                    {67, 100, 29}};

  std::sort(podaci.begin(), podaci.end(),
            [](std::list<int> &a, std::list<int> &b) {
              if (a.size() != b.size())
                return a.size() < b.size();

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
  std::cout << "Sortirani elementi po kriteriju: \n";
  for (auto &x : podaci) {
    for (auto &element : x) {
      std::cout << element << " ";
    }
    std::cout << "\n";
  }

  return 0;
}
