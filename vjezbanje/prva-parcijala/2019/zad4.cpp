// TP 2019/2020 Zadatak 4 (v2)
#include <iostream>
#include <list>
#include <vector>

template <typename TipSume, typename IterTip1, typename IterTip2>
void KumulativnaSuma(IterTip1 p1, IterTip1 p2, IterTip2 p3) {

  TipSume suma = TipSume();
  while (p1 != p2) {
    suma += *p1;
    *p3 = suma;
    p1++;
    p3++;
  }
}

int main() {

  int n;
  std::cout << "Koliko ima brojeva: ";
  std::cin >> n;

  std::list<int> a(n);
  std::cout << "Unesite brojeve: ";
  for (auto &x : a) {
    std::cin >> x;
  }

  std::vector<int> test(a.size());

  KumulativnaSuma<int>(a.begin(), a.end(), test.begin());

  for (auto &x : test) {
    std::cout << x << " ";
  }

  std::cout << std::endl;

  return 0;
}