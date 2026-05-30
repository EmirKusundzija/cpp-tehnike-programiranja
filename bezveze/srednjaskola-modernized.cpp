#include <exception>
#include <iostream>
#include <new>
#include <stdexcept>
#include <string>
// modernziacija zadatka iz srednje skole (dodavanje error handling-a)
class Vozilo {
  std::string model;
  int maksimalna_brzina;
  int godina_proizvodnje;

public:
  Vozilo(std::string M, int MB, int GP)
      : model(M), maksimalna_brzina(MB), godina_proizvodnje(GP) {
    if (MB <= 0 || MB > 200)
      throw std::range_error("Nevazeca maksimalna brzina");
    if (GP < 1 || GP > 2026)
      throw std::range_error("Nevazeca godina");
  }
  virtual ~Vozilo() = default;
  virtual void PrikaziDetalje() const {
    std::cout << "Model: " << model << "\n";
    std::cout << "Maksimalna brzina: " << maksimalna_brzina << "\n";
    std::cout << "Godina proizvodnje: " << godina_proizvodnje << "\n";
  }
  virtual int Starost() const { return 2026 - godina_proizvodnje; }
  virtual double IzracunajVozarinu(double cijena_goriva_po_litru,
                                   int broj_kilometara) = 0;
};

class Automobil : public Vozilo {
  int broj_vrata;

public:
  Automobil(std::string M, int MB, int GP, int BV)
      : Vozilo(M, MB, GP), broj_vrata(BV) {
    if (BV != 2 && BV != 4)
      throw std::domain_error("Nevazeci broj vrata!");
  }
  void PrikaziDetalje() const {
    Vozilo::PrikaziDetalje();
    std::cout << "Broj vrata: " << broj_vrata << "\n";
  }
  double IzracunajVozarinu(double cijena_goriva_po_litru, int broj_kilometara) {
    if (cijena_goriva_po_litru < 0 || broj_kilometara < 0)
      throw std::domain_error(
          "Nevazeca cijena goriva po litru ili nevazi broj kilometara");
    // 7 litara po 100 km
    double prosjecna_potrosnja = double(7) / 100;
    return cijena_goriva_po_litru * prosjecna_potrosnja * broj_kilometara;
  }
};

class Kamion : public Vozilo {
  double nosivost; // u tonama
public:
  Kamion(std::string M, int MB, int GP, double N)
      : Vozilo(M, MB, GP), nosivost(N) {
    if (N < 0)
      throw std::domain_error("Nevazeca nosivost");
  }
  void PrikaziDetalje() const {
    Vozilo::PrikaziDetalje();
    std::cout << "Nosivost: " << nosivost << "\n";
    std::cout << "Starost kamiona: " << Starost() << "\n";
  }
  double IzracunajVozarinu(double cijena_goriva_po_litru, int broj_kilometara) {
    if (cijena_goriva_po_litru < 0 || broj_kilometara < 0)
      throw std::domain_error(
          "Nevazeca cijena goriva po litru ili nevazi broj kilometara");
    // 15 litara po 100 km
    double prosjecna_potrosnja = double(15) / 100;
    return cijena_goriva_po_litru * prosjecna_potrosnja * broj_kilometara;
  }
};

int main() {
  try {

    Vozilo *vozila[2];
    vozila[0] = new Automobil("Toyota Corolla", 180, 2015, 4);
    vozila[1] = new Kamion("Volvo FH", 120, 2012, 18);

    for (int i = 0; i < 2; i++) {
      vozila[i]->PrikaziDetalje();
      std::cout << "Cijena voznje za 500km: "
                << vozila[i]->IzracunajVozarinu(2.35, 500) << " KM" << "\n";
    }

    for (int i = 0; i < 2; i++) {
      delete vozila[i];
    }
  } catch (std::bad_alloc &) {
    std::cout << "Problemi sa memorijom";
  }
  // test nevazece godine
  try {
    Automobil a("Toyota Corolla", 180, 2100, 4);
  } catch (std::exception &e) {
    std::cout << "Greska: " << e.what() << "!\n";
  }
  // test nevazecih parametara za funkciju izracunaj vozarinu;
  try {
    Automobil b("Toyota Corolla", 180, 2010, 4);
    std::cout << b.IzracunajVozarinu(-10, 100) << "\n";
  } catch (std::exception &e) {
    std::cout << "Greska: " << e.what() << "!\n";
  }
  return 0;
}
