#include <iostream>
#include <stack>

std::stack<double> PomnoziSaX(std::stack<double> s, double x) {
  std::stack<double> pomocni;

  while (!s.empty()) {
    pomocni.push(s.top() *= x);
    s.pop();
  }

  return pomocni;
}

int main() {
  int n;
  std::cout << "Unesite broj elemenata: ";
  std::cin >> n;
  std::stack<double> stek;
  std::cout << "Unesite elemente steka: ";
  for (int i = 0; i < n; i++) {
    double broj;
    std::cin >> broj;
    stek.push(broj);
  }

  std::stack<double> test_fja = PomnoziSaX(stek, 3);

  while (!test_fja.empty()) {
    std::cout << test_fja.top() << " ";
    test_fja.pop();
  }
  return 0;
}