#include <cmath>
#include <iostream>
#include <ostream>
#include <stdexcept>

class Kvadrat {
  double duzina_stranice;

public:
  explicit Kvadrat(double D) : duzina_stranice(D) {
    if (D <= 0)
      throw std::domain_error("Stranica ne moze biti negativna, niti 0");
  }
  void Postavi(const double &D) {
    if (D <= 0)
      throw std::domain_error("Stranica ne moze biti negativna, niti 0");
    duzina_stranice = D;
  }
  double DajDuzinuStranice() const { return duzina_stranice; }
  double DajPovrsinu() const { return duzina_stranice * duzina_stranice; }
  double DajObim() const { return duzina_stranice * 4; }
  void FaktorSkaliranja(double s) {
    if (s <= 0)
      throw std::domain_error(
          "Faktor skaliranja ne moze biti negativan, niti 0");
    duzina_stranice *= s;
  }
  void Ispisi() const {
    std::cout << "Duzina stranice: " << duzina_stranice << "\n";
    std::cout << "Obim: " << DajObim() << "\n";
    std::cout << "Povrsina: " << DajPovrsinu() << "\n";
  }
};

class Piramida {
  Kvadrat baza;
  double visina;

public:
  Piramida(Kvadrat B, double h) : baza(B), visina(h) {
    if (h < 0)
      throw std::domain_error("Visina ne moze biti negativna");
  }
  Piramida(double duzina_baze, double h) : baza(duzina_baze), visina(h) {
    if (h < 0)
      throw std::domain_error("Visina ne moze biti negativna");
  }

  void Postavi(const Kvadrat &B, double h) {
    if (h < 0)
      throw std::domain_error("Visina ne moze biti negativna");

    baza = B;
    visina = h;
  }
  void Postavi(double duzina_baze, double h) {
    if (h < 0)
      throw std::domain_error("Visina ne moze biti negativna");

    baza = Kvadrat(duzina_baze);
    visina = h;
  }
  Kvadrat DajBazu() const { return baza; }
  double DajVisinu() const { return visina; }
  double DajPovrsinu() const {
    return baza.DajPovrsinu() +
           visina * std::sqrt(baza.DajPovrsinu() + 4 * visina * visina);
  }
  double DajZapreminu() const { return (baza.DajPovrsinu() * visina) / 3.0; }
  void FaktorSkaliranja(double s) {
    if (s <= 0)
      throw std::domain_error(
          "Faktor skaliranja ne moze biti negativan, niti 0");

    baza.FaktorSkaliranja(s);
    visina *= s;
  }
  void Ispisi() const {
    std::cout << "Duzina baze: " << baza.DajDuzinuStranice() << "\n";
    std::cout << "Visina: " << visina << "\n";
    std::cout << "Povrsina piramide: " << DajPovrsinu() << "\n";
    std::cout << "Zapremina piramide: " << DajZapreminu() << "\n";
  }
};

int main() {
  Kvadrat a{5};
  a.Ispisi();
  a.FaktorSkaliranja(10);
  a.Ispisi();

  Piramida kul(2, 3);

  kul.Ispisi();

  kul.FaktorSkaliranja(2);
  kul.Ispisi();

  return 0;
}