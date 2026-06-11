#include <algorithm>
#include <cmath>
#include <iostream>

class Predmet {
  double gustina;

public:
  Predmet(double gustina) : gustina(gustina) {}
  virtual ~Predmet() = default;
  virtual double DajZapreminu() const = 0;
  double DajMasu() const { return gustina * DajZapreminu(); }
};

class Lopta : public Predmet {
  double r;
  static constexpr double PI = 3.141592653589793;

public:
  Lopta(double gustina, double r) : Predmet(gustina), r(r) {}
  double DajZapreminu() const override { return (4.0 * PI * r * r * r) / 3.0; }
};

class Cigla : public Predmet {
  double a, b, c;

public:
  Cigla(double gustina, double a, double b, double c)
      : Predmet(gustina), a(a), b(b), c(c) {}
  double DajZapreminu() const override { return a * b * c; }
};

int main() {

  const int broj_predmeta = 6;

  Predmet **niz = new Predmet *[broj_predmeta];

  niz[0] = new Lopta(0.75, 3.5);
  niz[1] = new Cigla(1.3, 3.4, 7.0, 2.15);
  niz[2] = new Lopta(1.2, 1.5);
  niz[3] = new Cigla(2.5, 8.0, 6.0, 5.0);
  niz[4] = new Lopta(2, 2.0);
  niz[5] = new Lopta(3.133, 23.0);

  std::sort(niz, niz + broj_predmeta, [](Predmet *p1, Predmet *p2) {
    return p1->DajMasu() > p2->DajMasu();
  });

  std::cout << "Mase predmeta nakon sortiranja u opadajucem poretku:\n";
  for (int i = 0; i < broj_predmeta; i++) {
    std::cout << "Predmet " << i + 1 << " Masa: " << niz[i]->DajMasu() << " kg"
              << "\n";
  }

  for (int i = 0; i < broj_predmeta; i++) {
    delete niz[i];
  }

  delete[] niz;

  return 0;
}