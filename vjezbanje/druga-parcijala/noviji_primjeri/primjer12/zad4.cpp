#include <cmath>
#include <iostream>
#include <stdexcept>
#include <utility>
class Tacka {
  std::pair<double, double> a;

public:
  Tacka(double x, double y) : a{x, y} {}
  double DajX() const { return a.first; }
  double DajY() const { return a.second; }
  Tacka &PostaviX(double x) {
    a.first = x;
    return *this;
  }
  Tacka &PostaviY(double y) {
    a.second = y;
    return *this;
  }
  // rastojanje je d = sqrt((x2-x1)^2+(y2-y1)^2)
  double operator-(const Tacka &t) const {
    double d = (t.DajX() - DajX()) * (t.DajX() - DajX()) +
               (t.DajY() - DajY()) * (t.DajY() - DajY());

    return std::sqrt(d);
  }
  friend std::ostream &operator<<(std::ostream &tok, const Tacka &t) {
    tok << "(" << t.a.first << "," << t.a.second << ")";
    return tok;
  }
};

class Krug {
  Tacka centar;
  double r;

public:
  Krug(Tacka centar, double r) : centar(centar), r(r) {}
  Krug(double x, double y, double r) : centar(x, y), r(r) {}
  Krug(Tacka centar, Tacka rub) : centar(centar) {
    r = centar - rub;
    if (r < 0) {
      throw std::domain_error("Neispravan poluprecnik");
    }
    if (r < 1e-5) {
      throw std::domain_error("Ne moze biti centar identican rubu");
    }
  }
  void Postavi(Tacka centar, double r) {
    this->centar = centar;
    if (r < 0) {
      throw std::domain_error("Neispravan poluprecnik");
    }
    this->r = r;
  }
  void Postavi(double x, double y, double r) {
    this->centar = {x, y};
    if (r < 0) {
      throw std::domain_error("Neispravan poluprecnik");
    }
    this->r = r;
  }
  void Postavi(Tacka centar, Tacka rub) {

    this->centar = centar;
    r = centar - rub;
    if (r < 0) {
      throw std::domain_error("Neispravan poluprecnik");
    }
    if (r < 1e-5) {
      throw std::domain_error("Ne moze biti centar identican rubu");
    }
  }
  double DajObim() const { return 2 * r * (std::atan(1) * 4); }
  double DajPovrsinu() const { return r * r * (std::atan(1) * 4); }
};

int main() {
  Tacka t1(2, 3);
  Tacka t2(5, 6);

  double rastojanje_test = t2 - t1;
  std::cout << rastojanje_test << "\n";

  std::cout << t1 << "\n";
  std::cout << t2 << "\n";
  return 0;
}