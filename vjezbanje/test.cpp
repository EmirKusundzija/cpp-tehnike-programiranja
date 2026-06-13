#include <complex>
#include <fstream>
#include <iostream>
#include <memory>
#include <utility> // zbog move
class KompleksniPametni {

  struct CvorPametni {
    std::unique_ptr<CvorPametni> veza;
    std::complex<double> element;
    CvorPametni(const std::complex<double> &el) : element(el), veza(nullptr) {}
  };
  std::unique_ptr<CvorPametni> pocetak;
  void DealocirajListu() {
    while (pocetak != nullptr) {
      pocetak = std::move(pocetak->veza);
    }
  }

public:
  KompleksniPametni() : pocetak(nullptr) {}
  ~KompleksniPametni() { DealocirajListu(); }

  void DodajNaPocetak(const std::complex<double> &el) {
    auto novi = std::make_unique<CvorPametni>(el);

    novi->veza = std::move(pocetak);

    pocetak = std::move(novi);
  }

  friend std::ostream &operator<<(std::ostream &tok,
                                  const KompleksniPametni &k) {
    for (CvorPametni *t = k.pocetak.get(); t != nullptr; t = t->veza.get()) {
      tok << t->element << " ";
    }
    return tok;
  }
};

int main() {
  KompleksniPametni a;

  a.DodajNaPocetak({1, 2});
  a.DodajNaPocetak({-1});
  a.DodajNaPocetak({0, 2});
  std::cout << a;

  return 0;
}
