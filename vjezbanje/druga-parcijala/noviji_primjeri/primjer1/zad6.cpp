// ovo je modifikovani zadatak koji koristi implementaciju Vektora pjeske
#include <algorithm>
#include <iostream>
#include <string>
class Artikal {
  std::string naziv;
  double cijena;

public:
  Artikal(std::string naziv, double cijena) : naziv(naziv), cijena(cijena) {}
  std::string DajNaziv() const { return naziv; }
  double DajCijenu() const { return cijena; }
  virtual Artikal *DajKopiju() const = 0;
  virtual void Ispisi() const = 0;
  virtual ~Artikal() = default;
};

class Brasno : public Artikal {
  double kilogrami;

public:
  Brasno(double cijena, double kilogrami)
      : Artikal("Brasno", cijena), kilogrami(kilogrami) {}
  double DajKilograme() const { return kilogrami; }
  void Ispisi() const override {
    std::cout << DajNaziv() << " " << kilogrami << "kg, " << DajCijenu()
              << "KM\n";
  }
  Artikal *DajKopiju() const override { return new Brasno(*this); }
};

class Ulje : public Artikal {
  double litri;

public:
  Ulje(double cijena, double litri) : Artikal("Ulje", cijena), litri(litri) {}
  void Ispisi() const override {
    std::cout << DajNaziv() << " " << litri << "l, " << DajCijenu() << "KM\n";
  }
  double DajLitre() const { return litri; }
  Artikal *DajKopiju() const override { return new Ulje(*this); }
};
// rucna implementaciaj vektora
template <typename T> class Vektor {
  T *elementi;
  int kapacitet, velicina;
  void Realociraj(int novi_kapacitet) {
    T *novi = nullptr;
    try {
      novi = new T[novi_kapacitet];
      for (int i{}; i < velicina; i++) {
        novi[i] = elementi[i];
      }
    } catch (...) {
      delete[] novi;
      throw;
    }
    delete[] elementi;
    elementi = novi;
    kapacitet = novi_kapacitet;
  }

public:
  Vektor() : elementi(new T[10]), kapacitet(10), velicina(0) {}
  ~Vektor() { delete[] elementi; }
  Vektor(const Vektor &drugi)
      : kapacitet(drugi.kapacitet), velicina(drugi.velicina) {
    elementi = new T[kapacitet];
    std::copy(drugi.elementi, drugi.elementi + velicina, elementi);
  }
  Vektor &operator=(const Vektor &drugi) {
    if (this != &drugi) {
      delete[] elementi;
      kapacitet = drugi.kapacitet;
      velicina = drugi.velicina;
      elementi = new T[kapacitet];
      std::copy(drugi.elementi, drugi.elementi + velicina, elementi);
    }
    return *this;
  }
  Vektor(Vektor &&drugi)
      : elementi(drugi.elementi), kapacitet(drugi.kapacitet),
        velicina(drugi.velicina) {
    drugi.velicina = drugi.kapacitet = 0;
    drugi.elementi = nullptr;
  }
  Vektor &operator=(Vektor &&drugi) {
    if (this != &drugi) {
      delete[] elementi;

      elementi = drugi.elementi;
      kapacitet = drugi.kapacitet;
      velicina = drugi.velicina;
      drugi.velicina = drugi.kapacitet = 0;
      drugi.elementi = nullptr;
    }
    return *this;
  }
  void DodajNaKraj(const T &element) {
    if (velicina == kapacitet)
      Realociraj(kapacitet + kapacitet / 2);
    elementi[velicina] = element;
    velicina++;
  }

  T *begin() { return elementi; }
  T *end() { return elementi + velicina; }
  const T *begin() const { return elementi; }
  const T *end() const { return elementi + velicina; }
  T &at(int indeks) {
    if (indeks < 0 || indeks >= velicina)
      throw std::out_of_range("Nevaljan pristup");
    return elementi[indeks];
  }
  const T &at(int indeks) const {
    if (indeks < 0 || indeks >= velicina)
      throw std::out_of_range("Nevaljan pristup");

    return elementi[indeks];
  }
  int DajVelicinu() const { return velicina; }
  T &operator[](int indeks) { return at(indeks); }
  const T &operator[](int indeks) const { return at(indeks); }
};

class Prodavnica {
  Vektor<Artikal *> artikli;

public:
  Prodavnica() = default;
  ~Prodavnica() {
    for (int i{}; i < artikli.DajVelicinu(); i++) {
      delete artikli[i];
    }
  }
  Prodavnica(const Prodavnica &p) {
    for (int i = 0; i < p.artikli.DajVelicinu(); i++) {
      artikli.DodajNaKraj(p.artikli[i]->DajKopiju());
    }
  }

  Prodavnica &operator=(const Prodavnica &p) {
    if (this != &p) {
      for (int i{}; i < artikli.DajVelicinu(); i++)
        delete artikli[i];

      artikli = Vektor<Artikal *>();

      for (int i{}; i < p.artikli.DajVelicinu(); i++)

        artikli.DodajNaKraj(p.artikli[i]->DajKopiju());
    }

    return *this;
  }
  Prodavnica(Prodavnica &&p) : artikli(std::move(p.artikli)) {}
  Prodavnica &operator=(Prodavnica &&p) {
    if (this != &p) {

      for (int i{}; i < artikli.DajVelicinu(); i++)
        delete artikli[i];

      artikli = std::move(p.artikli);
    }

    return *this;
  }
  void DodajUlje(const Ulje &u) { artikli.DodajNaKraj(u.DajKopiju()); }
  void DodajUlje(double cijena, double litri) {
    artikli.DodajNaKraj(new Ulje(cijena, litri));
  }
  void DodajBrasno(const Brasno &b) { artikli.DodajNaKraj(b.DajKopiju()); }
  void DodajBrasno(double cijena, double kilogrami) {
    artikli.DodajNaKraj(new Brasno(cijena, kilogrami));
  }
  Artikal *operator[](int indeks) { return artikli[indeks]; }
  const Artikal *operator[](int indeks) const { return artikli[indeks]; }
  void Ispisi() const {
    for (auto &x : artikli)
      x->Ispisi();
  }
};

int main() {
  Prodavnica p, p2;
  Ulje u(2, 1);
  Brasno b(1.1, 1);
  p.DodajUlje(u);
  p.DodajUlje(7, 5);
  p.DodajBrasno(17, 20);
  p.DodajBrasno(b);
  Prodavnica p3(p);
  p3.Ispisi(); // svaki artikal, u novom redu
  p2 = p;
  Artikal *a = p2[0];
  a->Ispisi();     // Ulje 1l, 2KM
  p2[2]->Ispisi(); // Brasno 17kg, 20KM
}
