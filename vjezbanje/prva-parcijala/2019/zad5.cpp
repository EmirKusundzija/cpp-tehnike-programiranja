// TP 2019/2020 Zadatak 5

#include <algorithm>
#include <cctype>
#include <cstring>
#include <iostream>
#include <string>

bool KriterijSortiranja(std::string &s1, std::string &s2) {

  auto f = [](std::string s) {
    for (auto &c : s) {
      c = std::tolower(c);
    }
    return s;
  };

  if (s1.length() != s2.length())
    return s1.length() < s2.length();

  return f(s1) < f(s2);
}

void SortirajPoDuzini(std::string *p, int n) {
  std::string *temp = new std::string[n];
  std::sort(p, p + n, KriterijSortiranja);

  delete[] temp;
}

int main() {
  int n;
  std::cout << "Koliko ima rijeci: ";
  std::cin >> n;

  try {
    std::string *niz = new std::string[n];
    std::cout << "Unesite rijeci: ";
    for (int i = 0; i < n; i++) {
      std::cin >> niz[i];
    }
    SortirajPoDuzini(niz, n);
    for (int i = 0; i < n; i++) {
      std::cout << niz[i] << " ";
    }
    delete[] niz;
  } catch (...) {
    std::cout << "Nestalo je memorije!";
  }
  return 0;
}
