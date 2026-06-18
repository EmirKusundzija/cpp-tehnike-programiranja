#include <iostream>
#include <stdexcept>

class CjelobrojniRed {
  struct Cvor {
    int element;
    Cvor *veza;
  };
  Cvor *pocetak;

public:
  CjelobrojniRed() : pocetak(nullptr) {}
  ~CjelobrojniRed() {
    while (pocetak) {
      Cvor *stari = pocetak;
      pocetak = pocetak->veza;
      delete stari;
    }
  }
  // pomocne metode (koje ce se samo primijeniti na operatore)
  void Guraj(int element) {
    Cvor *novi = new Cvor{element, nullptr};
    if (!pocetak) {
      pocetak = novi;
      return;
    }

    Cvor *t = pocetak;
    for (; t->veza != nullptr; t = t->veza)
      ;
    t->veza = novi;
  }
  int Naprijed() const {
    if (!pocetak)
      throw std::runtime_error("Red je prazan");
    return pocetak->element;
  }
  int Nazad() const {
    if (!pocetak)
      throw std::runtime_error("Red je prazan");

    Cvor *t = pocetak;
    for (; t->veza != nullptr; t = t->veza)
      ;
    return t->element;
  }
  int Velicina() const {
    int velicina{};
    for (Cvor *t = pocetak; t != nullptr; t = t->veza)
      velicina++;
    return velicina;
  }
  bool Prazan() const { return pocetak == nullptr; }
  // operatori
  CjelobrojniRed &operator+=(int element) {
    Guraj(element);
    return *this;
  }
  int operator*() const { return Naprijed(); }
  int operator~() const { return Nazad(); }
  bool operator!() const { return Prazan(); }
  int operator+() const { return Velicina(); }
  CjelobrojniRed operator+(const CjelobrojniRed &s1) {
    CjelobrojniRed rez;

    Cvor *t1 = pocetak;
    Cvor *t2 = s1.pocetak;

    while (t1 && t2) {
      rez += t1->element + t2->element;
      t1 = t1->veza;
      t2 = t2->veza;
    }
    return rez;
  }
  friend std::ostream &operator<<(std::ostream &tok, const CjelobrojniRed &r) {
    for (Cvor *t = r.pocetak; t != nullptr; t = t->veza) {
      tok << t->element;
      if (t->veza != nullptr)
        tok << ", ";
    }
    return tok;
  }
};

int main() {

  CjelobrojniRed s1;
  s1 += 3;
  s1 += 1;
  s1 += 5;
  CjelobrojniRed s2;
  s2 += -1;
  s2 += 101;
  s2 += 10;

  std::cout << s1 + s2;
  return 0;
}
