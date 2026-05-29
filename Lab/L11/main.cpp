#include <cmath>
#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <utility>

class Vektor3d {
  double *koordinate;
  mutable int brojac_ispisa = 0;

public:
  Vektor3d() : koordinate(new double[3]{0, 0, 0}) {}

  Vektor3d(double x, double y, double z) : koordinate(new double[3]{x, y, z}) {}

  Vektor3d(std::initializer_list<double> lista) : koordinate(new double[3]) {
    if (lista.size() != 3) {
      delete[] koordinate;
      throw std::domain_error("Pogresan broj koordinata");
    }

    auto it = lista.begin();
    koordinate[0] = *it++;
    koordinate[1] = *it++;
    koordinate[2] = *it;
  }

  Vektor3d(const Vektor3d &v)
      : koordinate(
            new double[3]{v.koordinate[0], v.koordinate[1], v.koordinate[2]}),
        brojac_ispisa(0) {}

  Vektor3d &operator=(const Vektor3d &v) {
    if (this != &v) {
      if (koordinate == nullptr)
        koordinate = new double[3];

      koordinate[0] = v.koordinate[0];
      koordinate[1] = v.koordinate[1];
      koordinate[2] = v.koordinate[2];

      brojac_ispisa = 0;
    }
    return *this;
  }

  Vektor3d(Vektor3d &&v) : koordinate(v.koordinate), brojac_ispisa(0) {
    v.koordinate = nullptr;
    v.brojac_ispisa = 0;
  }

  Vektor3d &operator=(Vektor3d &&v) {
    if (this != &v) {
      delete[] koordinate;
      koordinate = v.koordinate;
      brojac_ispisa = 0;

      v.koordinate = nullptr;
      v.brojac_ispisa = 0;
    }
    return *this;
  }

  ~Vektor3d() { delete[] koordinate; }

  void Postavi(double x, double y, double z) {
    koordinate[0] = x;
    koordinate[1] = y;
    koordinate[2] = z;
  }

  void Ocitaj(double &x, double &y, double &z) const {
    x = koordinate[0];
    y = koordinate[1];
    z = koordinate[2];
  }

  void Ispisi() const {
    std::cout << "{" << koordinate[0] << "," << koordinate[1] << ","
              << koordinate[2] << "}";
    brojac_ispisa++;
  }

  double DajX() const { return koordinate[0]; }
  double DajY() const { return koordinate[1]; }
  double DajZ() const { return koordinate[2]; }

  int DajBrojIspisa() const { return brojac_ispisa; }

  double DajDuzinu() const {
    return std::sqrt(koordinate[0] * koordinate[0] +
                     koordinate[1] * koordinate[1] +
                     koordinate[2] * koordinate[2]);
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
  return Vektor3d(v1.koordinate[0] + v2.koordinate[0],
                  v1.koordinate[1] + v2.koordinate[1],
                  v1.koordinate[2] + v2.koordinate[2]);
}

int main() {
  Vektor3d v1(3, 1, 4), v2;

  v1.Ispisi();
  v1.Ispisi();
  v1.Ispisi();
  v2.Ispisi();
  v2.Ispisi();
  std::cout << std::endl;

  std::cout << "Objekat v1 je ispisan " << v1.DajBrojIspisa()
            << " puta, a objekat v2 " << v2.DajBrojIspisa() << " puta"
            << std::endl;

  const Vektor3d v3 = v1;
  v3.Ispisi();
  std::cout << std::endl;
  std::cout << "Objekat v3 je ispisan " << v3.DajBrojIspisa() << " puta"
            << std::endl;

  std::cout << std::endl;

  Vektor3d v4{1, 2, 3};
  std::cout << "Sekvencijski konstruktor: ";
  v4.Ispisi();
  std::cout << std::endl;

  Vektor3d v5(v4);
  std::cout << "Kopirajuci konstruktor: ";
  v5.Ispisi();
  std::cout << std::endl;

  Vektor3d v6;
  v6 = v1;
  std::cout << "Kopirajuci operator dodjele: ";
  v6.Ispisi();
  std::cout << std::endl;

  Vektor3d pomocni1{7, 8, 9};
  Vektor3d v7(std::move(pomocni1));
  std::cout << "Pomjerajuci konstruktor: ";
  v7.Ispisi();
  std::cout << std::endl;

  Vektor3d pomocni2{10, 11, 12};
  Vektor3d v8;
  v8 = std::move(pomocni2);
  std::cout << "Pomjerajuci operator dodjele: ";
  v8.Ispisi();
  std::cout << std::endl;

  Vektor3d v9 = ZbirVektora(v4, v8);
  std::cout << "Zbir vektora: ";
  v9.Ispisi();
  std::cout << std::endl;

  std::cout << "Ulancavanje metoda: ";
  v4.PomnoziSaSkalarom(2).SaberiSa(v1).Ispisi();
  std::cout << std::endl;

  // bacanje izuzetka
  try {
    Vektor3d los{1, 2};
  } catch (const std::domain_error &e) {
    std::cout << "Izuzetak: " << e.what() << std::endl;
  }

  return 0;
}