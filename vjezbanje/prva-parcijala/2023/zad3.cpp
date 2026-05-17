// TP 2022/2023 Zadatak 3
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>
bool KubBroja(int n) {
  int rez = std::cbrt(n);
  return rez * rez * rez == n;
}

std::vector<bool> VektorKubovaBrojeva(const std::vector<int> &a) {

  std::vector<bool> rez;
  for (int i = 0; i < a.size(); i++) {
    if (a.at(i) < 0)
      throw std::domain_error("Ne moze element vektora biti negativan");
    rez.push_back(KubBroja(a.at(i)));
  }
  return rez;
}

int main() {

  std::vector<int> test{81, 27, 3, 6, 89, 36, 100, 400, 399, 10};
  try {
    std::vector<bool> fja = VektorKubovaBrojeva(test);

    for (int i = 0; i < fja.size(); i++) {
      std::cout << fja.at(i) << " ";
    }
  } catch (std::domain_error &err) {
    std::cout << err.what() << " ";
  }

  return 0;
}