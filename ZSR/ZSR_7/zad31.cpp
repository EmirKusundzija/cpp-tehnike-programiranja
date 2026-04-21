#include <iostream>
#include <stack>
#include <string>

std::stack<std::string> F(std::stack<std::string> &s,
                          const std::string &nadodavano) {
  std::stack<std::string> rez;
  while (!s.empty()) {
    rez.push(s.top() += nadodavano);
    s.pop();
  }

  return rez;
}

int main() {

  int n;

  std::cout << "Unesite broj stringova: ";
  std::cin >> n;
  std::cin.clear();
  std::cin.ignore(10000, '\n');

  std::stack<std::string> a;

  for (int i = 0; i < n; i++) {
    std::string unos;
    std::cin >> unos;
    a.push(unos);
  }
  std::cin.clear();
  std::cin.ignore(10000, '\n');
  std::string dodatak;
  std::cout << "Unesite dodatni string: ";
  std::getline(std::cin, dodatak);

  std::stack<std::string> test = F(a, dodatak);

  while (!test.empty()) {
    std::cout << test.top() << " ";
    test.pop();
  }
  return 0;
}