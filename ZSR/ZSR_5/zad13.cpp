#include <iostream>
#include <vector>

std::vector<int> StepeniBroja2(int n) {
  std::vector<int> rez;
  for (int i = 1; i < n; i *= 2) {
    rez.push_back(i);
  }
  return rez;
}

// v(i) = (3*v(i)^2+2) mod 17
void TransformPoPravilu(std::vector<int> &vec) {
  for (int i = 0; i < vec.size(); i++) {
    vec.at(i) = (3 * vec.at(i) * vec.at(i) + 2) % 17;
  }
}

void MinIMax(const std::vector<int> &vec, int &max, int &min) {
  min = max = vec.at(0);
  for (int i = 1; i < vec.size(); i++) {
    if (min > vec.at(i))
      min = vec.at(i);
    if (max < vec.at(i))
      max = vec.at(i);
  }
}

bool ImaTrocifrenihBrojeva(const std::vector<int> &vec) {
  for (auto &x : vec) {
    if (x >= 100 && x <= 999)
      return true;
  }
  return false;
}

template <typename PokTip> void IspisiKolekciju(PokTip *p1, PokTip *p2) {
  while (p1 != p2) {
    std::cout << *p1++ << " ";
  }
}

int main() {
  int broj;

  std::cout << "Unesite broj: ";
  std::cin >> broj;

  std::vector<int> test = StepeniBroja2(broj);

  TransformPoPravilu(test);

  int veliko, malo;
  MinIMax(test, veliko, malo);

  std::cout << "Razlika: " << veliko - malo << "\n";

  IspisiKolekciju(&test.at(0), &test[0] + test.size());
  return 0;
}