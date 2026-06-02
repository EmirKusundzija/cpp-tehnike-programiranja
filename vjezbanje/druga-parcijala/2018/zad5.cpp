#include <iostream>
#include <stack>
#include <stdexcept>

template <typename T>

std::ostream &operator<<(std::ostream &tok, std::stack<T> s) {
  while (!s.empty()) {
    tok << s.top() << " ";
    s.pop();
  }

  return tok;
}

template <typename T>
std::stack<T> operator-(std::stack<T> a, std::stack<T> b) {
  if (a.size() != b.size())
    throw std::domain_error("Stekovi moraju biti iste velicine");

  std::stack<T> rez;
  while (!a.empty()) {
    rez.push(a.top() - b.top());
    a.pop();
    b.pop();
  }
  return rez;
}

template <typename T> bool operator*(const std::stack<T> &s) {
  return !s.empty();
}

template <typename T>
std::stack<T> &operator*=(std::stack<T> &s, const T &broj) {
  std::stack<T> temp;
  while (!s.empty()) {
    temp.push(s.top() * broj);
    s.pop();
  }
  while (!temp.empty()) {
    s.push(temp.top());
    temp.pop();
  }
  return s;
}

int main() {
  int niz1[]{1, 5, 7, 3}, niz2[]{1, 9, 0, 4};
  std::stack<int> q1, q2;
  for (auto i : niz1)
    q1.push(i); // ubacimo elemente
  for (auto i : niz2)
    q2.push(i);                 // redoslijed je OBRNUT
  std::cout << q2 << std::endl; // 4 0 9 1 - ispis
  // moraju biti istih dimenzija, inace baciti izuzetak po volji!
  std::cout << q1 - q2; // 0, -4, 7, -1 ispis
  q1 *= 3;              // q1 = {9, 21, 15, 3} - redoslijed OBRNUT
  std::cout << q1 << std::endl;
  if (*q1)
    std::cout << "Nije prazan";
  else
    std::cout << "Prazan";
}