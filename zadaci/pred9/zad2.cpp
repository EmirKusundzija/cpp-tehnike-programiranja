#include <cmath>
#include <iostream>

class Vektor3d {
  double koordinate[3]; // x je na indeksu 0, a z koordinata je na indeksu 2
                        // (ide od 0 do n-1)

public:
  Vektor3d &Postavi(double x, double y, double z) {
    this->koordinate[0] = x;
    this->koordinate[1] = y;
    this->koordinate[2] = z;
    return *this;
  }
  void Ocitaj(double &x, double &y, double &z) const {
    x = koordinate[0];
    y = koordinate[1];
    z = koordinate[2];
  }
  void Ispisi() const {
    std::cout << "{" << this->koordinate[0] << "," << this->koordinate[1] << ","
              << this->koordinate[2] << "}";
  }
  double DajX() const { return koordinate[0]; }
  double DajY() const { return koordinate[1]; }
  double DajZ() const { return koordinate[2]; }
  Vektor3d &PostaviX(double x) {
    this->koordinate[0] = x;
    return *this;
  }
  Vektor3d &PostaviY(double y) {
    koordinate[1] = y;
    return *this;
  }
  Vektor3d &PostaviZ(double z) {
    koordinate[2] = z;
    return *this;
  }
  double DajDuzinu() const {

    double suma = 0;

    for (int i = 0; i < 3; i++) {
      suma += koordinate[i] * koordinate[i];
    }

    return std::sqrt(suma);
  }
  Vektor3d &PomnoziSaSkalarom(double s) {
    koordinate[0] *= s;
    koordinate[1] *= s;
    koordinate[2] *= s;
    return *this;
  }
  Vektor3d &SaberiSa(const Vektor3d &v) {
    koordinate[0] += v.koordinate[0];
    koordinate[1] += v.koordinate[1];
    koordinate[2] += v.koordinate[2];
    return *this;
  }
  friend Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2);
};

Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2) {
  Vektor3d v3;
  for (int i = 0; i < 3; i++)
    v3.koordinate[i] = v1.koordinate[i] + v2.koordinate[i];
  return v3;
}
int main() {
  auto NR = []() { std::cout << std::endl; };
  Vektor3d v1, v2;
  v1.Postavi(2, 5, 4);
  v1.Ispisi();
  NR(); // {2,5,4}
  double x, y, z;
  v1.Ocitaj(x, y, z);
  std::cout << x << " " << y << " " << z << std::endl; // 2 5 4
  std::cout << v1.DajX() << " " << v1.DajY() << " " << v1.DajZ()
            << std::endl; // 2 5 4
  v1.PostaviX(5);
  v1.PostaviY(-4);
  v1.PostaviZ(6);
  v1.Ispisi();
  NR(); // {5,-4,6}
  v1.PostaviX(3).PostaviY(0).PostaviZ(2).Ispisi();
  NR();                                     // {3,0,2}
  std::cout << v1.DajDuzinu() << std::endl; // 3.60555
  v2.Postavi(-8, 3, -9).Ispisi();
  NR(); // {-8,3,-9}
  v1.PomnoziSaSkalarom(3).SaberiSa(v2).PomnoziSaSkalarom(-1).Ispisi();
  NR(); // {-1,-3,3}
  v1.Ispisi();
  NR(); // {-1,-3,3}
  Vektor3d v3 = ZbirVektora(v1, v2);
  v3.Ispisi();
  NR(); // {-9,0,-6}
  ZbirVektora(v1, v2).Ispisi();
  NR(); // {-9,0,-6}
  const Vektor3d v4 = v3;
  v4.Ispisi();
  NR(); // {-9,0,-6}
  v4.Ocitaj(x, y, z);
  std::cout << x << " " << y << " " << z << std::endl; // -9 0 -6
  std::cout << v4.DajX() << " " << v4.DajY() << " " << v4.DajZ()
            << std::endl;                   // -9 0 -6
  std::cout << v4.DajDuzinu() << std::endl; // 10.8167
  return 0;
}
