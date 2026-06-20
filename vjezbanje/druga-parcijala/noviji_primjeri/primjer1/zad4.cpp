#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <vector>
template <typename T> class Skup {
  std::vector<T> elementi;

public:
  Skup() = default;
  Skup(std::initializer_list<T> lista) {
    for (auto &x : lista) {
      Dodaj(x);
    }
  }
  void Dodaj(const T &element) {
    if (ImaLiGa(element))
      return;
    elementi.push_back(element);
    std::sort(elementi.begin(), elementi.end());
  }
  int Velicina() const { return elementi.size(); }
  bool ImaLiGa(const T &element) const {

    for (int i = 0; i < elementi.size(); i++) {
      if (elementi.at(i) == element)
        return true;
    }
    return false;
  }
  void Obrisi(const T &element) {
    int pos = -1;

    for (int i = 0; i < elementi.size(); i++) {
      if (elementi[i] == element) {
        pos = i;
        break;
      }
    }

    if (pos == -1)
      return;

    for (int i = pos; i < elementi.size() - 1; i++) {
      elementi[i] = elementi[i + 1];
    }

    elementi.pop_back();
  }
  void Ispisi() const {
    std::for_each(elementi.begin(), elementi.end(),
                  [](const T &element) { std::cout << element << " "; });
  }
};

int main() {

  Skup<int> a{7, 3, 7, 1, 3};
  a.Ispisi();

  return 0;
}
