#include <cmath>
#include <iostream>
#include <stdexcept>
const double PI = std::atan(1) * 4;

class PravilniPoligon {
  int broj_stranica;
  double duzina_stranice;

public:
  PravilniPoligon(int broj_stranica, double duzina_stranice)
      : broj_stranica(broj_stranica), duzina_stranice(duzina_stranice) {
    if (broj_stranica < 3)
      throw std::domain_error("Ne postoji poligon sa 2 stranice");
    if (duzina_stranice <= 0)
      throw std::domain_error("Duzina stranice ne moze biti negativna");
  }

  void PostaviDuzinuStranice(double nova_duzina) {
    if (nova_duzina <= 0)
      throw std::domain_error(
          "Duzina novopostavljene stranice ne moze biti negativna");
    duzina_stranice = nova_duzina;
  }
  int DajBrojStranica() const { return broj_stranica; }
  double DajDuzinuStranice() const { return duzina_stranice; }
  double DajUnutrasnjiUgao() const { return (2 * PI) / broj_stranica; }
  double DajObim() const { return broj_stranica * duzina_stranice; }
  double DajPovrsinu() const {
    double brojnik = broj_stranica * duzina_stranice * duzina_stranice;
    double nazivnik = 4 * std::tan(DajUnutrasnjiUgao() / 2);
    return brojnik / nazivnik;
  }
};

class PravilnaPrizma {};

int main() {
  PravilniPoligon a(3, 5.11);

  // osnovne informacije
  std::cout << "Broj stranica: " << a.DajBrojStranica() << "\n";
  std::cout << "Duzina stranice: " << a.DajDuzinuStranice() << "\n";
  std::cout << "Unutrasnji ugao: " << a.DajUnutrasnjiUgao() << "\n";
  std::cout << "Obim = " << a.DajObim() << " Povrsina = " << a.DajPovrsinu()
            << "\n";
  return 0;
}
