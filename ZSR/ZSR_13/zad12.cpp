#include <algorithm>
#include <cmath>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
const double PI = std::atan(1) * 4;

class ApstraktanObjekat {
  double gustina;

public:
  ApstraktanObjekat(double gustina) : gustina(gustina) {}
  ~ApstraktanObjekat() = default;
  virtual void PrikaziInfo() const = 0;
  virtual double DajZapreminu() const = 0;
  double DajGustinu() const { return gustina; }
  virtual std::unique_ptr<ApstraktanObjekat> DajKopiju() const = 0;
  double DajTezinu() const { return DajGustinu() * DajZapreminu(); }
};

class Kvadar : public ApstraktanObjekat {
  double a, b, c;

public:
  Kvadar(double gustina, double a, double b, double c)
      : ApstraktanObjekat(gustina), a(a), b(b), c(c) {}
  double DajZapreminu() const override { return a * b * c; }
  std::unique_ptr<ApstraktanObjekat> DajKopiju() const override {
    return std::make_unique<Kvadar>(*this);
  }
  void PrikaziInfo() const override {
    std::cout << "Gustina: " << DajGustinu() << "\n";
    std::cout << "Stranice {a,b,c} = " << "{" << a << "," << b << "," << c
              << "}\n";
    std::cout << "Zapremina: " << DajZapreminu() << "\n";
    std::cout << "Tezina: " << DajTezinu() << "\n";
  }
};

class Lopta : public ApstraktanObjekat {
  double r;

public:
  Lopta(double gustina, double r) : ApstraktanObjekat(gustina), r(r) {}
  double DajZapreminu() const override { return (4 * r * r * r * PI) / 3.; }
  std::unique_ptr<ApstraktanObjekat> DajKopiju() const override {
    return std::make_unique<Lopta>(*this);
  }
  void PrikaziInfo() const override {
    std::cout << "Gustina: " << DajGustinu() << "\n";
    std::cout << "Poluprecnik: " << r << "\n";
    std::cout << "Zapremina: " << DajZapreminu() << "\n";
    std::cout << "Tezina: " << DajTezinu() << "\n";
  }
};

class Valjak : public ApstraktanObjekat {
  double r, h;

public:
  Valjak(double gustina, double r, double h)
      : ApstraktanObjekat(gustina), r(r), h(h) {}
  std::unique_ptr<ApstraktanObjekat> DajKopiju() const override {
    return std::make_unique<Valjak>(*this);
  }
  double DajZapreminu() const override { return h * r * r * PI; }
  void PrikaziInfo() const override {
    std::cout << "Gustina: " << DajGustinu() << "\n";
    std::cout << "Poluprecnik baze i visina: " << "{" << r << "," << h << "}"
              << "\n";
    std::cout << "Zapremina: " << DajZapreminu() << "\n";
    std::cout << "Tezina: " << DajTezinu() << "\n";
  }
};

class KontejnerTijela {
  std::vector<std::unique_ptr<ApstraktanObjekat>> tijela;

public:
  KontejnerTijela() = default;

  KontejnerTijela(const KontejnerTijela &druga) {
    for (const auto &t : druga.tijela) {
      tijela.emplace_back(t->DajKopiju());
    }
  }

  KontejnerTijela &operator=(const KontejnerTijela &druga) {
    if (this != &druga) {
      tijela.clear();
      for (const auto &t : druga.tijela) {
        tijela.emplace_back(t->DajKopiju());
      }
    }
    return *this;
  }

  ~KontejnerTijela() = default;

  KontejnerTijela(KontejnerTijela &&) = default;
  KontejnerTijela &operator=(KontejnerTijela &&) = default;

  void KreirajKvadar(double gustina, double a, double b, double c) {
    tijela.emplace_back(std::make_unique<Kvadar>(gustina, a, b, c));
  }
  void KreirajLoptu(double gustina, double r) {
    tijela.emplace_back(std::make_unique<Lopta>(gustina, r));
  }
  void KreirajValjak(double gustina, double r, double h) {
    tijela.emplace_back(std::make_unique<Valjak>(gustina, r, h));
  }

  int BrojObjekata() const { return tijela.size(); }

  ApstraktanObjekat &DajNajlaksi() {
    if (tijela.empty())
      throw std::range_error("Kolekcija je prazna!");

    auto min_it =
        std::min_element(tijela.begin(), tijela.end(),
                         [](const std::unique_ptr<ApstraktanObjekat> &t1,
                            const std::unique_ptr<ApstraktanObjekat> &t2) {
                           return t1->DajTezinu() < t2->DajTezinu();
                         });
    return **min_it;
  }

  ApstraktanObjekat &DajNajtezi() {
    if (tijela.empty())
      throw std::range_error("Kolekcija je prazna!");

    auto max_it =
        std::max_element(tijela.begin(), tijela.end(),
                         [](const std::unique_ptr<ApstraktanObjekat> &t1,
                            const std::unique_ptr<ApstraktanObjekat> &t2) {
                           return t1->DajTezinu() < t2->DajTezinu();
                         });
    return **max_it;
  }

  ApstraktanObjekat &operator[](int i) {
    if (i < 0 || i >= tijela.size()) {
      throw std::out_of_range("Indeks je izvan opsega!");
    }
    return *tijela[i];
  }

  const ApstraktanObjekat &operator[](int i) const {
    if (i < 0 || i >= tijela.size()) {
      throw std::out_of_range("Indeks je izvan opsega!");
    }
    return *tijela[i];
  }

  int PrekoTezine(double granica) const {
    int brojac = 0;
    for (const auto &t : tijela) {
      if (t->DajTezinu() > granica)
        brojac++;
    }
    return brojac;
  }

  void SortirajPoTezini() {
    std::sort(tijela.begin(), tijela.end(),
              [](const std::unique_ptr<ApstraktanObjekat> &t1,
                 const std::unique_ptr<ApstraktanObjekat> &t2) {
                return t1->DajTezinu() < t2->DajTezinu();
              });
  }
};

int main() { return 0; }