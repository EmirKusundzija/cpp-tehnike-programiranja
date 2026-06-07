#include <cmath>
#include <iostream>

class Vektor3d {
  double x, y, z;
  mutable int broj_ispisa = 0;

public:
  Vektor3d &Postavi(double x, double y, double z) {
    Vektor3d::x = x;
    Vektor3d::y = y;
    Vektor3d::z = z;
    return *this;
  }
  void Ocitaj(double &x, double &y, double &z) const {
    x = Vektor3d::x;
    y = Vektor3d::y;
    z = Vektor3d::z;
  }
  void Ispisi() const {
    std::cout << "{" << x << "," << y << "," << z << "}";
    broj_ispisa++;
  }
  double DajX() const { return x; }
  double DajY() const { return y; }
  double DajZ() const { return z; }
  Vektor3d &PostaviX(double x) {
    this->x = x;
    return *this;
  }
  Vektor3d &PostaviY(double y) {
    this->y = y;
    return *this;
  }
  Vektor3d &PostaviZ(double z) {
    this->z = z;
    return *this;
  }
  double DajDuzinu() const { return std::sqrt(x * x + y * y + z * z); }
  Vektor3d &PomnoziSaSkalarom(double s) {
    x *= s;
    y *= s;
    z *= s;
    return *this;
  }
  Vektor3d &SaberiSa(const Vektor3d &v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }
  friend Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2);

  Vektor3d PomnoziSaSkalarom(double s) const {
    Vektor3d v; // Novi vektor!
    v.x = x * s;
    v.y = y * s;
    v.z = z * s;
    return v;
  }
  Vektor3d SaberiSa(const Vektor3d &v) const {
    Vektor3d v1; // Novi vektor!
    v1.x = x + v.x;
    v1.y = y + v.y;
    v1.z = z + v.z;
    return v1;
  }
  int DajBrojIspisa() const { return broj_ispisa; }
};

Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2) {
  Vektor3d v3;
  v3.x = v1.x + v2.x;
  v3.y = v1.y + v2.y;
  v3.z = v1.z + v2.z;
  return v3;
}
int main() {
  Vektor3d v1, v2;
  v1.Postavi(3, 4, 2);
  v2.Postavi(2, 0, 5);
  v1.Ispisi();
  v1.Ispisi();
  v1.Ispisi();
  v2.Ispisi();
  v2.Ispisi();
  std::cout << std::endl;
  std::cout << "Objekat v1 je ispisan " << v1.DajBrojIspisa()
            << "puta , a objekat v2 " << v2.DajBrojIspisa() << " puta"
            << std::endl;
  return 0;
}
