#include <iostream>
#include <stdexcept>

class Pravougaonik {
  // a - duza stranica
  // b - kraca stranica
  double a = 0, b = 0;

public:
  Pravougaonik &Postavi(double a, double b) {
    if (a < 0 || b < 0)
      throw std::domain_error("Ne mogu stranice biti negativne");
    this->a = a;
    this->b = b;
    return *this;
  }
  double DajDuzuStranicu() const { return a; }
  double DajKracuStranicu() const { return b; }
  double DajPovrsinuPravougaonika() const { return a * b; };
  double DajObimPravougaonika() const { return 2 * a + 2 * b; }
  bool DaLiJeKvadrat() const { return a == b; }
  bool DaLiJePoravnatHorizontalno() const { return a > b; }
  bool DaLiJePoravnatVertikalno() const { return b > a; }
  Pravougaonik &RotirajZa90Stepeni() {
    double temp = this->a;
    this->a = this->b;
    this->b = temp;
    return *this;
  }
  Pravougaonik &SkalirajPravougaonik(double faktor_skaliranja_a,

                                     double faktor_skaliranja_b) {
    if (faktor_skaliranja_a < 0 || faktor_skaliranja_b < 0)
      throw std::domain_error("Faktori skaliranja su negativni");

    this->a *= faktor_skaliranja_a;
    this->b *= faktor_skaliranja_b;
    return *this;
  }
};
int main() { return 0; }