#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <vector>

template <typename T> class Skup {
  std::vector<T> v;

public:
  Skup() = default;
  Skup(std::initializer_list<T> a) {

    std::for_each(a.begin(), a.end(), [this](const T &element) {
      auto it = std::find(v.begin(), v.end(), element);

      if (it == v.end())
        v.push_back(element);
    });
    std::sort(v.begin(), v.end());
  }
  int Velicina() const { return v.size(); }
  void Dodaj(const T &element) {

    auto it = std::find(v.begin(), v.end(), element);

    if (it == v.end()) {
      v.push_back(element);
      std::sort(v.begin(), v.end());
    }
  }
  bool ImaLiGa(const T &element) const {
    auto it = std::find(v.begin(), v.end(), element);
    return it != v.end();
  }
  void Izbrisi(const T &element) {
    auto it = std::find(v.begin(), v.end(), element);
    if (it != v.end())
      v.erase(it);
  }
  void Ispisi() const {
    std::for_each(v.begin(), v.end(),
                  [](const T &element) { std::cout << element << "\n"; });
  }
};

int main() {
  Skup<int> a{2, 1, 3, 3, 5};
  a.Ispisi();
  std::cout << "\n";
  a.Dodaj(10);
  a.Dodaj(7);
  a.Dodaj(7);
  std::cout << "\n";
  std::cout << "Ima li element 7 u ovom skupu? "
            << (a.ImaLiGa(7) ? "Ima" : "Nema");
  a.Ispisi();
  return 0;
}