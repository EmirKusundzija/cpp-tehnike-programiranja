#include <iostream>
#include <memory>
#include <vector>

class Vozilo {
  int tezina;

public:
  explicit Vozilo(int tezina) : tezina(tezina) {}
  int DajTezinu() const { return tezina; }
  virtual int DajUkupnuTezinu() const = 0;
  virtual Vozilo *DajKopiju() const = 0;
  virtual void IspisiPodatke() const = 0;
};

class Automobil : public Vozilo {

  std::vector<int> tezine;

public:
  Automobil(int tezina, std::vector<int> tezine)
      : Vozilo(tezina), tezine(tezine) {}
  int DajUkupnuTezinu() const override {
    int suma{};
    for (auto &x : tezine)
      suma += x;
    return suma + DajTezinu();
  }
  void IspisiPodatke() const override {
    std::cout << "Vrsta vozila: Automobil\n";
    std::cout << "Vlastita tezina: " << DajTezinu() << " kg\n";
    std::cout << "Tezine putnika: ";
    for (int i{}; i < tezine.size(); i++) {
      if (i > 0)
        std::cout << ", ";
      std::cout << tezine.at(i) << " kg";
    }
    std::cout << "\nUkupna tezina: " << DajUkupnuTezinu() << " kg\n";
  }
  Vozilo *DajKopiju() const override { return new Automobil(*this); }
};

class Kamion : public Vozilo {
  int tezina_tereta;

public:
  Kamion(int tezina, int tezina_tereta)
      : Vozilo(tezina), tezina_tereta(tezina_tereta) {}
  Vozilo *DajKopiju() const override { return new Kamion(*this); }
  int DajUkupnuTezinu() const override { return DajTezinu() + tezina_tereta; }
  void IspisiPodatke() const override {
    std::cout << "Vrsta vozila: Kamion\n";
    std::cout << "Vlastita tezina: " << DajTezinu() << " kg\n";
    std::cout << "Tezina tereta: " << tezina_tereta << " kg\n";
    std::cout << "Ukupna tezina: " << DajUkupnuTezinu() << " kg\n";
  }
};

class Autobus : public Vozilo {
  int broj_putnika;
  int prosjecna_tezina;

public:
  Autobus(int tezina, int broj_putnika, int prosjecna_tezina)
      : Vozilo(tezina), broj_putnika(broj_putnika),
        prosjecna_tezina(prosjecna_tezina) {}
  int DajUkupnuTezinu() const override {
    return DajTezinu() + (broj_putnika * prosjecna_tezina);
  }
  Vozilo *DajKopiju() const override { return new Autobus(*this); }
  void IspisiPodatke() const override {
    std::cout << "Vrsta vozila: Kamion\n";
    std::cout << "Vlastita tezina: " << DajTezinu() << " kg\n";
    std::cout << "Broj putnika: " << broj_putnika << "\n";
    std::cout << "Ukupna tezina: " << DajUkupnuTezinu() << " kg\n";
  }
};

int main() {

  Automobil a(700, {80, 90, 60});

  a.IspisiPodatke();
  return 0;
}