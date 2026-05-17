// TP 2022/2023 Zadatak 4

#include <iostream>
#include <vector>

using Matrica = std::vector<std::vector<double>>;

bool JeIdempotentna(Matrica &mat) {
  if (mat.empty() || mat.at(0).empty()) {
    return false;
  }
  for (int i = 0; i < mat.size(); i++) {
    for (int j = 0; j < mat.at(i).size(); j++) {
      double suma = 0;
      for (int k = 0; k < mat.size(); k++) {
        suma += mat.at(i).at(k) * mat.at(k).at(j);
      }
      if (std::abs(suma - mat.at(i).at(j)) > 1e-9) {
        return false;
      }
    }
  }

  return true;
}

int main() {
  Matrica A{{1, 0}, {0, 0}};
  bool test = JeIdempotentna(A);

  std::cout << std::boolalpha << test << " ";

  return 0;
}