#include <iostream>
#include <stdexcept>
#include <vector>

std::vector<double> Fun(std::vector<double> A, std::vector<int> B) {
  std::vector<double> rezultat;

  for (int i = 0; i < B.size(); i++) {
    rezultat.push_back(A.at(B.at(i)));
    if (B.at(i) < 0 || B.at(i) > A.size())
      throw std::range_error("Nelegalan indeks");
  }
  return rezultat;
}

int main() {
  try {
    std::vector<double> a{2.3, 68.7, 0.3, 416, 4674};

    std::vector<int> b = {4, 4, 0, 1};

    std::vector<double> rez = Fun(a, b);

    for (auto x : rez) {
      std::cout << x << " ";
    }
  } catch (std::range_error &e) {
    std::cout << "Greska: " << e.what() << "\n";
  }
  return 0;
}