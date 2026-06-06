// TP 2025/2026: Zadaća 5, Zadatak 2
#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <stdexcept>
class Padavine {
  std::list<int> kolekcija_padavina;
  int max_kolicina;

public:
  explicit Padavine(int kolicina) : max_kolicina(kolicina) {
    if (kolicina <= 0)
      throw std::range_error("Ilegalna maksimalna kolicina");
  }
  void RegistrirajPadavine(int kolicina);
  int DajBrojRegistriranihPadavina() const { return kolekcija_padavina.size(); }
  void BrisiSve() { kolekcija_padavina.clear(); }
  friend std::ostream &operator<<(std::ostream &tok, const Padavine &p);
};

void Padavine::RegistrirajPadavine(int kolicina) {
  if (kolicina < 0 || kolicina > max_kolicina)
    throw std::range_error("Ilegalna kolicina padavina");

  kolekcija_padavina.push_back(kolicina);
}
std::ostream &operator<<(std::ostream &tok, const Padavine &p) {
  std::list<int> kopija(p.kolekcija_padavina);
  kopija.sort(std::greater<int>());
  std::copy(kopija.begin(), kopija.end(),
            std::ostream_iterator<int>(tok, "\n"));
  return tok;
}

int main() { return 0; }
