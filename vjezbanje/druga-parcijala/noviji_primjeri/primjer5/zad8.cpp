#include <cmath>
#include <iostream>
#include <vector>
class GeometrijskoTijelo {
public:
  GeometrijskoTijelo() = default;
  virtual ~GeometrijskoTijelo() = default;
  virtual double DajPovrsinu() const = 0;
  virtual double DajZapreminu() const = 0;
  virtual GeometrijskoTijelo *DajKopiju() const = 0;
};

class Kvadar : public GeometrijskoTijelo {
  double a, b, c;

public:
  Kvadar(double a, double b, double c) : a(a), b(b), c(c) {}
  double DajPovrsinu() const override { return 2 * (a * b + a * c + b * c); }
  double DajZapreminu() const override { return a * b * c; }
  GeometrijskoTijelo *DajKopiju() const override { return new Kvadar(*this); }
};
class Kugla : public GeometrijskoTijelo {
  double r;
  static double PI;

public:
  explicit Kugla(double r) : r(r) {}
  double DajPovrsinu() const override { return 4 * PI * r * r; }
  double DajZapreminu() const override { return (4.0 / 3.0) * PI * r * r * r; }
  GeometrijskoTijelo *DajKopiju() const override { return new Kugla(*this); }
};

class Valjak : public GeometrijskoTijelo {
  double r, h;
  static double PI;

public:
  Valjak(double r, double h) : r(r), h(h) {}
  double DajPovrsinu() const override { return 2 * PI * r * (r + h); }
  double DajZapreminu() const override { return r * r * PI * h; }
  GeometrijskoTijelo *DajKopiju() const override { return new Valjak(*this); }
};

double Kugla::PI = std::atan(1) * 4;
double Valjak::PI = std::atan(1) * 4;

int main() {

  std::vector<GeometrijskoTijelo *> tijela;
  Kugla a(2);
  Valjak b(2, 3);
  Kvadar c(10, 20, 30);
  tijela.push_back(a.DajKopiju());
  tijela.push_back(b.DajKopiju());
  tijela.push_back(c.DajKopiju());

  for (auto &x : tijela) {
    std::cout << x->DajPovrsinu() << "\n";
    std::cout << x->DajZapreminu() << "\n";
  }
}
