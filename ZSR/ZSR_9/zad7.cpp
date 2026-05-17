#include <cmath>
#include <iostream>
#include <stdexcept>

class Krug {
  double poluprecnik = 0.0;

public:
  Krug &Postavi(double novi_poluprecnik) {
    if (novi_poluprecnik < 0)
      throw std::domain_error("Ne moze poluprecnik biti negativan");

    poluprecnik = novi_poluprecnik;

    return *this;
  }
  double DajDuzinuPoluprecnika() const { return poluprecnik; }
  double DajObimKruga() const { return 2 * poluprecnik * atan(1) * 4; }
  double DajPovrsinuKruga() const {
    return poluprecnik * poluprecnik * atan(1) * 4;
  }
  Krug &SkalirajKrug(double faktor_skaliranja) {
    if (faktor_skaliranja < 0)
      throw std::domain_error("Faktor skaliranja ne moze biti negativan");
    poluprecnik = poluprecnik * faktor_skaliranja;
    return *this;
  }

  void Ispisi() const {
    std::cout << "Poluprecnik: " << poluprecnik << "\n";
    std::cout << "Obim kruga: " << DajObimKruga() << "\n";
    std::cout << "Povrsina kruga: " << DajPovrsinuKruga() << "\n";
  }
};

int main() {
  Krug a;

  a.Postavi(4);

  a.Ispisi();

  a.SkalirajKrug(4);

  a.Ispisi();
  // postavljanje negativnog poluprecnika
  try {
    a.Postavi(-2);
    a.Ispisi();
  } catch (std::domain_error &e) {
    std::cout << "Greska: " << e.what() << "\n";
  }
  // postavljanje negativnog faktora skaliranja
  try {
    a.Postavi(2);
    a.SkalirajKrug(-100);
    a.Ispisi();
  } catch (std::domain_error &e) {
    std::cout << "Greska: " << e.what() << "\n";
  }
  // Ulancavanje
  a.SkalirajKrug(40).Ispisi();
  return 0;
}