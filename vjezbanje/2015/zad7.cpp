#include <algorithm>
#include <deque>
#include <iostream>

int main() {
  std::deque<int> a{123, 563, 991, 13, 6, 93, 100, 686, 313, 151};

  std::sort(a.begin(), a.end(), [](int x, int y) {
    int obrnut1 = 0;
    int temp1 = x;
    while (temp1 > 0) {
      obrnut1 = obrnut1 * 10 + (temp1 % 10);
      temp1 /= 10;
    }
    int obrnut2 = 0;
    int temp2 = y;
    while (temp2 > 0) {
      obrnut2 = obrnut2 * 10 + (temp2 % 10);
      temp2 /= 10;
    }
    return obrnut1 < obrnut2;
  });

  std::cout << "Rezultat: \n";
  for (auto &x : a) {
    std::cout << x << " ";
  }
  return 0;
}