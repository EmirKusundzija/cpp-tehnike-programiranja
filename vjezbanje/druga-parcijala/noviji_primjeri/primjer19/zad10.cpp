#include <iostream>
#include <set>
#include <utility>
template <typename Tip1, typename Tip2>
std::set<std::pair<Tip1, Tip2>> operator*(const std::set<Tip1> &s1,
                                          const std::set<Tip2> &s2) {
  int velicina = s1.size() * s2.size();

  std::set<std::pair<Tip1, Tip2>> rez;
  for (auto &a : s1) {
    for (auto &b : s2) {
      rez.insert(std::make_pair(a, b));
    }
  }
  return rez;
}

int main() {
  std::set<int> a{1, 2, 3};
  std::set<double> b{3.14, 9.81, 2.7, 6.67};
  auto P = a * b;
  for (auto &p : P) {
    std::cout << "(" << p.first << "," << p.second << ")";
  }
}