#include <iostream>
#include <vector>

template <typename ProizvoljanTip>
bool DaLiJeSimetrican(std::vector<ProizvoljanTip> vec) {
  for (int i = 0, j = vec.size() - 1; i < j; i++, j--)
    if (vec.at(i) != vec.at(j))
      return false;
  return true;
}

int main() {
  int n;
  std::cout << "Unesite n: ";
  std::cin >> n;

  std::vector<long long int> test(n);

  for (auto &x : test) {
    std::cin >> x;
  }

  if (DaLiJeSimetrican(test)) {
    std::cout << "Simetrican je!";
  } else
    std::cout << "Nije simetrican!";

  return 0;
}