// TP 2025/2026: Zadaća 5, Zadatak 4
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

class ApstraktnoVozilo {
  int tezina_vozila;

public:
  ApstraktnoVozilo(int tezina) : tezina_vozila(tezina) {}

  int DajTezinu() const { return tezina_vozila; }

  virtual int DajUkupnuTezinu() const = 0;
  virtual ApstraktnoVozilo *DajKopiju() const = 0;
  virtual void IspisiPodatke() const = 0;

  virtual ~ApstraktnoVozilo() = default;
};

class Automobil : public ApstraktnoVozilo {
  std::vector<int> tezine_putnika;

public:
  Automobil(int tezina, std::vector<int> tezine_putnika)
      : ApstraktnoVozilo(tezina), tezine_putnika(std::move(tezine_putnika)) {}

  int DajUkupnuTezinu() const override {
    int ukupna_tezina = DajTezinu();
    for (int tezina_putnika : tezine_putnika)
      ukupna_tezina += tezina_putnika;
    return ukupna_tezina;
  }

  ApstraktnoVozilo *DajKopiju() const override { return new Automobil(*this); }

  void IspisiPodatke() const override {
    std::cout << "Vrsta vozila: Automobil\n"
              << "Vlastita tezina: " << DajTezinu() << " kg\n"
              << "Tezine putnika: ";

    for (std::size_t i = 0; i < tezine_putnika.size(); i++) {
      std::cout << tezine_putnika[i] << " kg";
      if (i + 1 != tezine_putnika.size())
        std::cout << ", ";
    }

    std::cout << "\nUkupna tezina: " << DajUkupnuTezinu() << " kg\n";
  }
};

class Kamion : public ApstraktnoVozilo {
  int tezina_tereta;

public:
  Kamion(int tezina, int tezina_tereta)
      : ApstraktnoVozilo(tezina), tezina_tereta(tezina_tereta) {}

  int DajUkupnuTezinu() const override { return DajTezinu() + tezina_tereta; }

  ApstraktnoVozilo *DajKopiju() const override { return new Kamion(*this); }

  void IspisiPodatke() const override {
    std::cout << "Vrsta vozila: Kamion\n"
              << "Vlastita tezina: " << DajTezinu() << " kg\n"
              << "Tezina tereta: " << tezina_tereta << " kg\n"
              << "Ukupna tezina: " << DajUkupnuTezinu() << " kg\n";
  }
};

class Autobus : public ApstraktnoVozilo {
  int broj_putnika;
  int prosjecna_tezina_putnika;

public:
  Autobus(int tezina, int broj_putnika, int prosjecna_tezina_putnika)
      : ApstraktnoVozilo(tezina), broj_putnika(broj_putnika),
        prosjecna_tezina_putnika(prosjecna_tezina_putnika) {}

  int DajUkupnuTezinu() const override {
    return DajTezinu() + broj_putnika * prosjecna_tezina_putnika;
  }

  ApstraktnoVozilo *DajKopiju() const override { return new Autobus(*this); }

  void IspisiPodatke() const override {
    std::cout << "Vrsta vozila: Autobus\n"
              << "Vlastita tezina: " << DajTezinu() << " kg\n"
              << "Broj putnika: " << broj_putnika << '\n'
              << "Prosjecna tezina putnika: " << prosjecna_tezina_putnika
              << " kg\n"
              << "Ukupna tezina: " << DajUkupnuTezinu() << " kg\n";
  }
};

class Vozilo {
  ApstraktnoVozilo *p;

  void Test() const {
    if (!p)
      throw std::logic_error("Nespecificirano vozilo");
  }

public:
  Vozilo() : p(nullptr) {}

  Vozilo(const ApstraktnoVozilo &vozilo) : p(vozilo.DajKopiju()) {}

  ~Vozilo() { delete p; }

  Vozilo(const Vozilo &drugo)
      : p(drugo.p == nullptr ? nullptr : drugo.p->DajKopiju()) {}

  Vozilo(Vozilo &&drugo) noexcept : p(drugo.p) { drugo.p = nullptr; }

  Vozilo &operator=(const Vozilo &drugo) {
    if (this != &drugo) {
      ApstraktnoVozilo *novi =
          drugo.p == nullptr ? nullptr : drugo.p->DajKopiju();
      delete p;
      p = novi;
    }
    return *this;
  }

  Vozilo &operator=(Vozilo &&drugo) noexcept {
    if (this != &drugo)
      std::swap(p, drugo.p);
    return *this;
  }

  int DajTezinu() const {
    Test();
    return p->DajTezinu();
  }

  int DajUkupnuTezinu() const {
    Test();
    return p->DajUkupnuTezinu();
  }

  void IspisiPodatke() const {
    Test();
    p->IspisiPodatke();
  }
};

void ProvjeriKrajReda(std::istringstream &tok) {
  tok >> std::ws;
  if (!tok.eof())
    throw std::logic_error("Datoteka sadrzi besmislene podatke");
}

std::vector<Vozilo> UcitajVozila(const std::string &ime_datoteke) {
  std::ifstream ulaz(ime_datoteke);
  if (!ulaz)
    throw std::logic_error("Trazena datoteka ne postoji");

  std::vector<Vozilo> vozila;
  std::string red;

  while (std::getline(ulaz, red)) {
    if (!red.empty() && red.back() == '\r')
      red.pop_back();

    if (red.empty())
      throw std::logic_error("Datoteka sadrzi besmislene podatke");

    std::istringstream tok(red);
    char vrsta;
    tok >> vrsta;

    if (!tok)
      throw std::logic_error("Datoteka sadrzi besmislene podatke");

    if (vrsta == 'A') {
      int tezina, broj_putnika;
      if (!(tok >> tezina >> broj_putnika) || tezina < 0 || broj_putnika < 0)
        throw std::logic_error("Datoteka sadrzi besmislene podatke");

      std::vector<int> tezine_putnika;
      for (int i = 0; i < broj_putnika; i++) {
        int tezina_putnika;
        if (!(tok >> tezina_putnika) || tezina_putnika < 0)
          throw std::logic_error("Datoteka sadrzi besmislene podatke");
        tezine_putnika.push_back(tezina_putnika);
      }

      ProvjeriKrajReda(tok);
      vozila.push_back(Automobil(tezina, tezine_putnika));
    } else if (vrsta == 'K') {
      int tezina, tezina_tereta;
      if (!(tok >> tezina >> tezina_tereta) || tezina < 0 || tezina_tereta < 0)
        throw std::logic_error("Datoteka sadrzi besmislene podatke");

      ProvjeriKrajReda(tok);
      vozila.push_back(Kamion(tezina, tezina_tereta));
    } else if (vrsta == 'B') {
      int tezina, broj_putnika, prosjecna_tezina_putnika;
      if (!(tok >> tezina >> broj_putnika >> prosjecna_tezina_putnika) ||
          tezina < 0 || broj_putnika < 0 || prosjecna_tezina_putnika < 0)
        throw std::logic_error("Datoteka sadrzi besmislene podatke");

      ProvjeriKrajReda(tok);
      vozila.push_back(
          Autobus(tezina, broj_putnika, prosjecna_tezina_putnika));
    } else {
      throw std::logic_error("Datoteka sadrzi besmislene podatke");
    }
  }

  if (ulaz.bad())
    throw std::logic_error("Problemi pri citanju datoteke");

  return vozila;
}

int main() {
  try {
    Automobil automobil(700, {80, 90, 60});
    Kamion kamion(1600, 850);
    Autobus autobus(2500, 30, 75);

    std::cout << "Podaci o automobilu:\n";
    automobil.IspisiPodatke();
    std::cout << "\nPodaci o kamionu:\n";
    kamion.IspisiPodatke();
    std::cout << "\nPodaci o autobusu:\n";
    autobus.IspisiPodatke();

    Vozilo vozilo1(automobil);
    Vozilo vozilo2(kamion);
    Vozilo vozilo3(autobus);

    std::cout << "\nVlastita tezina vozila1: " << vozilo1.DajTezinu()
              << " kg\n";
    std::cout << "Ukupna tezina vozila1: " << vozilo1.DajUkupnuTezinu()
              << " kg\n";

    Vozilo kopija(vozilo1);
    Vozilo dodijeljeno;
    dodijeljeno = vozilo2;
    Vozilo pomjereno(std::move(vozilo3));
    Vozilo pomjeranjem_dodijeljeno;
    pomjeranjem_dodijeljeno = std::move(pomjereno);

    std::cout << "Ukupna tezina kopiranog vozila: "
              << kopija.DajUkupnuTezinu() << " kg\n";
    std::cout << "Ukupna tezina dodijeljenog vozila: "
              << dodijeljeno.DajUkupnuTezinu() << " kg\n";
    std::cout << "Ukupna tezina pomjerenog vozila: "
              << pomjeranjem_dodijeljeno.DajUkupnuTezinu() << " kg\n";

    try {
      Vozilo nespecificirano;
      std::cout << nespecificirano.DajTezinu() << '\n';
    } catch (const std::logic_error &e) {
      std::cout << e.what() << '\n';
    }

    {
      std::ofstream datoteka("VOZILA.TXT");
      datoteka << "A500 3 80 60 75\n"
               << "K1500 1200\n"
               << "B2200 50 80\n"
               << "A700 0\n";
    }

    std::vector<Vozilo> vozila = UcitajVozila("VOZILA.TXT");

    std::sort(vozila.begin(), vozila.end(),
              [](const Vozilo &v1, const Vozilo &v2) {
                return v1.DajUkupnuTezinu() < v2.DajUkupnuTezinu();
              });

    std::cout << "\nUkupne tezine vozila nakon sortiranja:\n";
    for (const auto &vozilo : vozila)
      std::cout << vozilo.DajUkupnuTezinu() << '\n';
  } catch (const std::exception &e) {
    std::cout << e.what() << '\n';
  }

  return 0;
}
