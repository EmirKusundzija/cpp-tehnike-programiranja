#include <iostream>
#include <vector>

void DodajSuprotne(std::vector<int> &vec) {
  for (int i = 0; i < vec.size(); i += 2) {
    vec.insert(vec.begin() + i + 1, -vec[i]);
  }
}

int main() {
  int n;
  std::cout << "Koliko ima brojeva: ";
  std::cin >> n;

  std::vector<int> brojevi(n);
  std::cout << "Unesite brojeve: ";
  for (auto &x : brojevi) {
    std::cin >> x;
  }
  DodajSuprotne(brojevi);
  std::cout << "Brojevi nakon dodavanja: ";
  for (auto &x : brojevi) {
    std::cout << x << " ";
  }

  return 0;
}