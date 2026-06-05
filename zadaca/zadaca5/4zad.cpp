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

static void ProvjeriKrajReda(std::istringstream &tok) {
  tok >> std::ws;
  if (!tok.eof())
    throw std::logic_error("Datoteka sadrzi besmislene podatke");
}

static std::vector<Vozilo> UcitajVozila(const std::string &ime_datoteke) {
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
      tezine_putnika.reserve(static_cast<std::size_t>(broj_putnika));

      for (int i = 0; i < broj_putnika; i++) {
        int tezina_putnika;
        if (!(tok >> tezina_putnika) || tezina_putnika < 0)
          throw std::logic_error("Datoteka sadrzi besmislene podatke");
        tezine_putnika.push_back(tezina_putnika);
      }

      ProvjeriKrajReda(tok);
      vozila.emplace_back(Automobil(tezina, std::move(tezine_putnika)));
    } else if (vrsta == 'K') {
      int tezina, tezina_tereta;
      if (!(tok >> tezina >> tezina_tereta) || tezina < 0 || tezina_tereta < 0)
        throw std::logic_error("Datoteka sadrzi besmislene podatke");

      ProvjeriKrajReda(tok);
      vozila.emplace_back(Kamion(tezina, tezina_tereta));
    } else if (vrsta == 'B') {
      int tezina, broj_putnika, prosjecna_tezina_putnika;
      if (!(tok >> tezina >> broj_putnika >> prosjecna_tezina_putnika) ||
          tezina < 0 || broj_putnika < 0 || prosjecna_tezina_putnika < 0)
        throw std::logic_error("Datoteka sadrzi besmislene podatke");

      ProvjeriKrajReda(tok);
      vozila.emplace_back(
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
    std::vector<Vozilo> vozila = UcitajVozila("VOZILA.TXT");

    std::sort(vozila.begin(), vozila.end(),
              [](const Vozilo &v1, const Vozilo &v2) {
                return v1.DajUkupnuTezinu() < v2.DajUkupnuTezinu();
              });

    for (const auto &vozilo : vozila)
      std::cout << vozilo.DajUkupnuTezinu() << '\n';
  } catch (const std::exception &e) {
    std::cout << e.what() << '\n';
  }

  return 0;
}
