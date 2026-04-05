#include <cmath>
#include <iostream>
#include <stdexcept>

#include <vector>
bool KubBroja(int broj) {
  const double epsilon = 1e-9;
  int kub = std::cbrt(broj);
  return std::abs(pow(kub, 3) - broj) < epsilon; // |a-b| < eps
}

std::vector<bool> KuboviBroja(std::vector<int> vec) {
  std::vector<bool> v;
  for (int i = 0; i < vec.size(); i++) {
    if (vec.at(i) < 0)
      throw std::domain_error("Element vektora ne smije biti negativan");
    v.push_back(KubBroja(vec.at(i)));
  }
  return v;
}

int main() {
  try {
    std::vector<bool> test(
        KuboviBroja({216, 8, 8, 10, 577, 27, 86, 5343, 839, 252}));
    for (auto x : test) {
      std::cout << std::boolalpha << x << " ";
    }
    std::cout << std::endl;
  } catch (std::domain_error &e) {
    std::cout << "Greska: " << e.what() << "\n";
  }

  return 0;
}