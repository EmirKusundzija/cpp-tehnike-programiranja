
#include <iostream>
#include <iterator>
#include <list>

template <typename IterTip1, typename IterTip2>
IterTip2 PrekopirajSimetricno(IterTip1 p1, IterTip1 p2, IterTip2 p3) {

  while (p1 != p2) {
    *p3 = *p1;
    p1++;
    p3++;
  }
  return p3;
}

int main() {
  int n;
  std::cout << "Unesite broj elemenata: ";
  std::cin >> n;

  std::list<int> a(n);

  for (auto &x : a) {
    std::cin >> x;
  }

  auto p1 = a.begin();
  auto p2 = a.end();

  std::list<int> b;

  auto test = PrekopirajSimetricno(p1, p2, std::front_inserter(b));

  while (p1 != p2) {
    std::cout << *p1++;
    if (p1 != p2)
      std::cout << ", ";
  }
  auto p1b = b.begin();
  auto p2b = b.end();
  while (p1b != p2b) {
    std::cout << *p1b++;
    if (p1b != p2b)
      std::cout << ", ";
  }

  return 0;
}