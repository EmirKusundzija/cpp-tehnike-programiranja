#include <iostream>

template <typename Tip> class MojaLista {
  struct Cvor {
    Tip info;
    Cvor *veza;
  };
  Cvor *pocetak;

  void Obrisi() {
    while (pocetak != nullptr) {
      Cvor *stari = pocetak;

      pocetak = pocetak->veza;
      delete stari;
    }
  }

public:
  MojaLista() : pocetak(nullptr) {}
  ~MojaLista() { Obrisi(); }
  void PushFront(Tip element) {
    Cvor *novi = new Cvor{element, pocetak};
    pocetak = novi;
  }
  MojaLista &operator+=(const Tip &el) {
    PushBack(el);
    return *this;
  }
  void PushBack(Tip element) {
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
  Tip &operator[](int indeks) {
    Cvor *t = pocetak;

    for (int i{}; i < indeks; i++) {
      t = t->veza;
    }
    return t->info;
  }
  friend std::ostream &operator<<(std::ostream &tok, const MojaLista &s) {
    for (Cvor *t = s.pocetak; t != nullptr; t = t->veza) {
      tok << t->info;

      if (t->veza != nullptr)
        tok << ", ";
    }
    return tok;
  }
  MojaLista operator+(const MojaLista &l) {
    MojaLista<Tip> rez;

    for (Cvor *t = pocetak; t != nullptr; t = t->veza) {
      rez += t->info;
    }

    for (Cvor *t = l.pocetak; t != nullptr; t = t->veza) {
      rez += t->info;
    }

    return rez;
  }
};

int main() {
  MojaLista<int> l1;
  l1 += 10; // Dodaj na kraj
  l1 += 20;
  l1 += 30;
  std::cout << l1;
  std::cout << "Element na indeksu 1: " << l1[1] << "\n"; // Ispisuje: 20

  MojaLista<int> l2;
  l2 += 100;
  l2 += 200;

  // Spajanje operatorom +
  MojaLista<int> spojena = l1 + l2;

  std::cout << "Elementi spojene liste:\n";
  std::cout << spojena[0] << " " << spojena[1] << " " << spojena[2] << " "
            << spojena[3] << " " << spojena[4] << "\n";
  // Treba ispisati: 10 20 30 100 200

  return 0;
}