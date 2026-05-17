#include <iostream>
#include <stack>

template <typename T>
std::stack<T> PomnoziStek(std::stack<T> &s, T vrijednost) {
  std::stack<T> rez;
  while (!s.empty()) {
    rez.push(s.top() * vrijednost);
    s.pop();
  }

  while (!rez.empty()) {
    s.push(rez.top());
    rez.pop();
  }

  return s;
}

int main() {
  int n;
  std::cout << "Velicina steka: ";
  std::cin >> n;

  std::stack<double> s;
  std::cout << "Unesite elemente: ";
  for (int i = 0; i < n; i++) {
    double broj;
    std::cin >> broj;
    s.push(broj);
  }
  double mnozilac;
  std::cout << "Unesite mnozilac: ";
  std::cin >> mnozilac;

  std::stack<double> rez = PomnoziStek(s, mnozilac);

  while (!rez.empty()) {
    std::cout << rez.top() << " ";
    rez.pop();
  }
  return 0;
}