#include <iostream>
#include <stdexcept>

template <typename TipElemenata> struct Cvor {
  TipElemenata element;
  Cvor *veza;
};

template <typename TipElemenata> class Stek {
  Cvor<TipElemenata> *vrh{};
  void Ocisti() {
    while (vrh != nullptr) {
      Cvor<TipElemenata> *staro = vrh;
      vrh = vrh->veza;
      delete staro;
    }
  }

public:
  Stek() : vrh(nullptr) {}
  ~Stek() { Ocisti(); }
  Stek(Stek &&s) : vrh(s.vrh) { s.vrh = nullptr; }
  Stek &operator=(Stek &&s) {
    if (this != &s) {
      Ocisti();
    }
    vrh = s.vrh;
    s.vrh = nullptr;
    return *this;
  }
  void DodajNaVrh(TipElemenata element) {
    Cvor<TipElemenata> *novi = new Cvor<TipElemenata>{element, vrh};
    vrh = novi;
  }
  Stek(const Stek &s) = delete;
  Stek &operator=(const Stek &s) = delete;
  void SkiniSaVrha() {
    if (vrh == nullptr)
      throw std::domain_error("Prazan stek");
    Cvor<TipElemenata> *staro = vrh;

    vrh = vrh->veza;

    delete staro;
  }

  const TipElemenata &DajVrh() const {
    if (vrh == nullptr)
      throw std::domain_error("Prazan stek");
    return vrh->element;
  }
  TipElemenata &DajVrh() {
    if (vrh == nullptr)
      throw std::domain_error("Prazan stek");
    return vrh->element;
  }
  int DajVelicinu() const {
    int brojac{};
    for (Cvor<TipElemenata> *t = vrh; t != nullptr; t = t->veza) {
      brojac++;
    }
    return brojac;
  }
  bool DaLiJePrazan() const { return vrh == nullptr; }
  void Ispisi() const {
    for (Cvor<TipElemenata> *t = vrh; t != nullptr; t = t->veza) {

      std::cout << t->element;
      if (t->veza != nullptr)
        std::cout << "/";
    }
  }
};

int main() {
  Stek<int> a;
  a.DodajNaVrh(3);
  a.DodajNaVrh(5);
  a.DodajNaVrh(2);
  a.DodajNaVrh(8);
  a.DodajNaVrh(4);
  a.Ispisi();
  std::cout << "Velicina iznosi: " << a.DajVelicinu() << "\n";
  std::cout << "Vrh je: " << a.DajVrh() << "\n";
  std::cout << "Prazan: " << a.DaLiJePrazan();

  Stek<double> b;

  std::cout << "Prazan: " << b.DaLiJePrazan();
  return 0;
}