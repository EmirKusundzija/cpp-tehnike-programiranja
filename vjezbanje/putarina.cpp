#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
class Vozilo {
  std::string tablice;
  double osnovna_cijena;

public:
  Vozilo(std::string tablice, double osnovna_cijena)
      : tablice(tablice), osnovna_cijena(osnovna_cijena) {}
  virtual ~Vozilo() = default;
  double DajOsnovnuCijenu() const { return osnovna_cijena; }
  virtual double ObracunajPutarinu() const = 0;
  virtual Vozilo *DajKopiju() const = 0;
  virtual void Ispisi(std::ostream &tok) const {
    tok << "Tablice: " << tablice << "\n";
    tok << "Osnovna cijena: " << osnovna_cijena << "\n";
    tok << "Putarina: " << ObracunajPutarinu() << "\n";
  }
};

class GustoVozilo : public Vozilo {
  int broj_osovina;

public:
  GustoVozilo(std::string tablice, double osnovna_cijena, int broj_osovina)
      : Vozilo(tablice, osnovna_cijena), broj_osovina(broj_osovina) {}
  double ObracunajPutarinu() const override {
    return broj_osovina * DajOsnovnuCijenu();
  }
  Vozilo *DajKopiju() const override { return new GustoVozilo(*this); }
  void Ispisi(std::ostream &tok) const override {
    Vozilo::Ispisi(tok);
    tok << "Broj osovina: " << broj_osovina << "\n";
  }
};

class EkoVozilo : public Vozilo {
  double procenat_subvencije;

public:
  EkoVozilo(std::string tablice, double osnovna_cijena, double PS)
      : Vozilo(tablice, osnovna_cijena), procenat_subvencije(PS) {}
  Vozilo *DajKopiju() const override { return new EkoVozilo(*this); }
  double ObracunajPutarinu() const override {
    double proc = procenat_subvencije / 100.0;
    return proc * DajOsnovnuCijenu();
  }
  void Ispisi(std::ostream &tok) const override {
    Vozilo::Ispisi(tok);
    tok << "Procenat subvencije: " << procenat_subvencije << "\n";
  }
};

class NaplatnaStanica {
  std::vector<std::unique_ptr<Vozilo>> vozila;

public:
  NaplatnaStanica() = default;
  void DodajVozilo(Vozilo &v) { vozila.emplace_back(v.DajKopiju()); }
  double UkupniPrihod() const {
    double suma = 0;
    std::for_each(vozila.begin(), vozila.end(),
                  [&suma](const std::unique_ptr<Vozilo> &p) {
                    suma += p->ObracunajPutarinu();
                  });
    return suma;
  }
};

int main() {

  Vozilo *a = new EkoVozilo("223", 5, 4);
  a->Ispisi(std::cout);
  Vozilo *b = new GustoVozilo("U23-5-111", 34, 4);
  b->Ispisi(std::cout);

  return 0;
}