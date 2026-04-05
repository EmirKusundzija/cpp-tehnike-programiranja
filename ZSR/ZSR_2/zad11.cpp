#include <iostream>
#include <vector>

std::vector<double> FILO(double niz[], int n) {
  std::vector<double> v;
  for (int i = n - 1; i >= 0; i--) {
    v.push_back(niz[i]);
  }
  return v;
}

int main() {
  int n;
  std::cout << "Unesite br. elemenata niza: ";
  std::cin >> n;
  const int br_elemenata = 1000;
  double a[br_elemenata]; // najgori scenario

  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  std::vector<double> vec = FILO(a, n);
  // niz[] = {1,2,3}
  // vector = {3,2,1}

  for (int i = 0; i < n; i++) {
    std::cout << " " << vec.at(i);
  }
  return 0;
}