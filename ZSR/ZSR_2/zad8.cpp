#include <cmath>
#include <iostream>
#include <vector>

bool SviElementiSuJednaki(std::vector<double> brojevi) {
  const double epsilon = 1e-9;
  for (int i = 0; i < brojevi.size(); i++) {
    for (int j = i + 1; j < brojevi.size(); j++) {
      if (std::abs(brojevi.at(i) - brojevi.at(j)) > epsilon)
        return false;
    }
  }
  return true;
}

bool SviElementiSuRazliciti(std::vector<double> brojevi) {
  const double epsilon = 1e-9;
  for (int i = 0; i < brojevi.size(); i++) {
    for (int j = i + 1; j < brojevi.size(); j++) {
      if (std::abs(brojevi.at(i) - brojevi.at(j)) < epsilon)
        return false;
    }
  }
  return true;
}

void IspisVektora(std::vector<double> v) {
  bool prvi_element = true;
  for (auto i : v) {

    if (!prvi_element)
      std::cout << ", ";
    std::cout << i;
    prvi_element = false;
  }
}

int main() {
  // Testni program
  int n;
  std::cout << "Unesite n: ";
  std::cin >> n;
  std::vector<double> elementi;
  for (int i = 0; i < n; i++) {
    double broj;
    std::cin >> broj;
    elementi.push_back(broj);
  }
  if (SviElementiSuJednaki(elementi)) {
    std::cout << "Elementi: ";

    IspisVektora(elementi);
    std::cout << " su jednaki!";
  }

  if (SviElementiSuRazliciti(elementi)) {
    std::cout << "Elementi: ";

    IspisVektora(elementi);
    std::cout << " nisu jednaki!";
  }

  return 0;
}