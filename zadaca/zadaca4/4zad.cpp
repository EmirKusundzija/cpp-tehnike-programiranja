// TP 2025/2026: Zadaća 4, Zadatak 4
#include <algorithm>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

class Polazak {
  std::string odrediste, oznaka_voznje;
  int broj_perona, sat_polaska, minute_polaska, trajanje_voznje, kasnjenje;

  static bool IspravnoVrijeme(int sati, int minute) {
    return sati >= 0 && sati <= 23 && minute >= 0 && minute <= 59;
  }

  static std::pair<int, int> IzMinuta(int ukupno_minuta) {
    const int minuta_u_danu = 24 * 60;
    ukupno_minuta %= minuta_u_danu;
    if (ukupno_minuta < 0)
      ukupno_minuta += minuta_u_danu;
    return {ukupno_minuta / 60, ukupno_minuta % 60};
  }

  static std::string FormatirajVrijeme(std::pair<int, int> vrijeme) {
    std::string rezultat;
    if (vrijeme.first < 10)
      rezultat += '0';
    rezultat += std::to_string(vrijeme.first);
    rezultat += ':';
    if (vrijeme.second < 10)
      rezultat += '0';
    rezultat += std::to_string(vrijeme.second);
    return rezultat;
  }

public:
  Polazak(std::string_view odrediste, std::string_view oznaka_voznje,
          int broj_perona, int sat_polaska, int minute_polaska,
          int trajanje_voznje);

  void PostaviKasnjenje(int kasnjenje);
  bool DaLiKasni() const { return kasnjenje > 0; }
  int DajTrajanje() const { return trajanje_voznje; }

  std::pair<int, int> DajOcekivanoVrijemePolaska() const;
  std::pair<int, int> DajOcekivanoVrijemeDolaska() const;

  void Ispisi() const;
};

Polazak::Polazak(std::string_view odrediste, std::string_view oznaka_voznje,
                 int broj_perona, int sat_polaska, int minute_polaska,
                 int trajanje_voznje)
    : odrediste(odrediste), oznaka_voznje(oznaka_voznje),
      broj_perona(broj_perona), sat_polaska(sat_polaska),
      minute_polaska(minute_polaska), trajanje_voznje(trajanje_voznje),
      kasnjenje(0) {

  if (odrediste.empty() || oznaka_voznje.empty() || broj_perona < 1 ||
      broj_perona > 15)
    throw std::domain_error("Pogresna oznaka");

  if (!IspravnoVrijeme(sat_polaska, minute_polaska))
    throw std::domain_error("Pogresno vrijeme");

  if (trajanje_voznje <= 0)
    throw std::domain_error("Pogresno trajanje voznje");
}

void Polazak::PostaviKasnjenje(int kasnjenje) {
  if (kasnjenje < 0)
    throw std::domain_error("Pogresan unos kasnjenja");

  Polazak::kasnjenje = kasnjenje;
}

std::pair<int, int> Polazak::DajOcekivanoVrijemePolaska() const {
  return IzMinuta(sat_polaska * 60 + minute_polaska + kasnjenje);
}

std::pair<int, int> Polazak::DajOcekivanoVrijemeDolaska() const {
  return IzMinuta(sat_polaska * 60 + minute_polaska + trajanje_voznje +
                  kasnjenje);
}

void Polazak::Ispisi() const {
  std::cout << std::left << std::setw(10) << oznaka_voznje << std::setw(30)
            << odrediste << std::right;

  if (!DaLiKasni()) {
    std::cout << std::setw(10)
              << FormatirajVrijeme(DajOcekivanoVrijemePolaska())
              << std::setw(10)
              << FormatirajVrijeme(DajOcekivanoVrijemeDolaska()) << std::setw(8)
              << broj_perona << std::endl;
  } else {
    std::cout << std::setw(10)
              << FormatirajVrijeme(DajOcekivanoVrijemePolaska())
              << " (Planirano "
              << FormatirajVrijeme({sat_polaska, minute_polaska}) << ", Kasni "
              << std::setw(3) << kasnjenje << " min)" << std::endl;
  }
}

class Polasci {
  std::vector<std::shared_ptr<Polazak>> polasci;

  static int VrijemeUMinutama(std::pair<int, int> vrijeme) {
    return vrijeme.first * 60 + vrijeme.second;
  }

public:
  Polasci() = default;
  Polasci(std::initializer_list<Polazak> lista_polazaka);
  ~Polasci() = default;

  Polasci(const Polasci &p);
  Polasci(Polasci &&p);

  Polasci &operator=(const Polasci &p);
  Polasci &operator=(Polasci &&p);

  void RegistrirajPolazak(std::string_view odrediste,
                          std::string_view oznaka_voznje, int broj_perona,
                          int sat_polaska, int minute_polaska,
                          int trajanje_voznje);

  void RegistrirajPolazak(std::shared_ptr<Polazak> p);
  void RegistrirajPolazak(Polazak *p);

  int DajBrojPolazaka() const { return static_cast<int>(polasci.size()); }
  int DajBrojPolazakaKojiKasne() const;

  Polazak &DajPrviPolazak();
  Polazak DajPrviPolazak() const;

  Polazak &DajPosljednjiPolazak();
  Polazak DajPosljednjiPolazak() const;

  void Ispisi() const;
  void IsprazniKolekciju() { polasci.clear(); }
};

Polasci::Polasci(std::initializer_list<Polazak> lista_polazaka) {
  polasci.reserve(lista_polazaka.size());

  for (const Polazak &p : lista_polazaka)
    polasci.push_back(std::make_shared<Polazak>(p));
}

Polasci::Polasci(const Polasci &p) {
  polasci.reserve(p.polasci.size());

  for (const auto &polazak : p.polasci)
    polasci.push_back(std::make_shared<Polazak>(*polazak));
}

Polasci::Polasci(Polasci &&p) : polasci(std::move(p.polasci)) {
  p.polasci.clear();
}

Polasci &Polasci::operator=(const Polasci &p) {
  if (this != &p) {
    std::vector<std::shared_ptr<Polazak>> novi_polasci;
    novi_polasci.reserve(p.polasci.size());

    for (const auto &polazak : p.polasci)
      novi_polasci.push_back(std::make_shared<Polazak>(*polazak));

    polasci = std::move(novi_polasci);
  }

  return *this;
}

Polasci &Polasci::operator=(Polasci &&p) {
  if (this != &p) {
    polasci = std::move(p.polasci);
    p.polasci.clear();
  }

  return *this;
}

void Polasci::RegistrirajPolazak(std::string_view odrediste,
                                 std::string_view oznaka_voznje,
                                 int broj_perona, int sat_polaska,
                                 int minute_polaska, int trajanje_voznje) {

  polasci.push_back(std::make_shared<Polazak>(odrediste, oznaka_voznje,
                                              broj_perona, sat_polaska,
                                              minute_polaska, trajanje_voznje));
}

void Polasci::RegistrirajPolazak(std::shared_ptr<Polazak> p) {
  if (p == nullptr)
    throw std::domain_error("Neispravan polazak");

  polasci.push_back(p);
}

void Polasci::RegistrirajPolazak(Polazak *p) {
  if (p == nullptr)
    throw std::domain_error("Neispravan polazak");

  polasci.push_back(std::make_shared<Polazak>(*p));
}

int Polasci::DajBrojPolazakaKojiKasne() const {
  return static_cast<int>(std::count_if(
      polasci.begin(), polasci.end(),
      [](const std::shared_ptr<Polazak> &p) { return p->DaLiKasni(); }));
}

Polazak &Polasci::DajPrviPolazak() {
  if (polasci.empty())
    throw std::domain_error("Nema registriranih polazaka");

  return **std::min_element(
      polasci.begin(), polasci.end(),
      [](const std::shared_ptr<Polazak> &p1,
         const std::shared_ptr<Polazak> &p2) {
        return VrijemeUMinutama(p1->DajOcekivanoVrijemePolaska()) <
               VrijemeUMinutama(p2->DajOcekivanoVrijemePolaska());
      });
}

Polazak Polasci::DajPrviPolazak() const {
  if (polasci.empty())
    throw std::domain_error("Nema registriranih polazaka");

  return **std::min_element(
      polasci.begin(), polasci.end(),
      [](const std::shared_ptr<Polazak> &p1,
         const std::shared_ptr<Polazak> &p2) {
        return VrijemeUMinutama(p1->DajOcekivanoVrijemePolaska()) <
               VrijemeUMinutama(p2->DajOcekivanoVrijemePolaska());
      });
}

Polazak &Polasci::DajPosljednjiPolazak() {
  if (polasci.empty())
    throw std::domain_error("Nema registriranih polazaka");

  return **std::max_element(
      polasci.begin(), polasci.end(),
      [](const std::shared_ptr<Polazak> &p1,
         const std::shared_ptr<Polazak> &p2) {
        return VrijemeUMinutama(p1->DajOcekivanoVrijemePolaska()) <
               VrijemeUMinutama(p2->DajOcekivanoVrijemePolaska());
      });
}

Polazak Polasci::DajPosljednjiPolazak() const {
  if (polasci.empty())
    throw std::domain_error("Nema registriranih polazaka");

  return **std::max_element(
      polasci.begin(), polasci.end(),
      [](const std::shared_ptr<Polazak> &p1,
         const std::shared_ptr<Polazak> &p2) {
        return VrijemeUMinutama(p1->DajOcekivanoVrijemePolaska()) <
               VrijemeUMinutama(p2->DajOcekivanoVrijemePolaska());
      });
}

void Polasci::Ispisi() const {
  if (polasci.empty())
    return;

  std::vector<std::shared_ptr<Polazak>> kopija_pokazivaca(polasci);

  std::sort(kopija_pokazivaca.begin(), kopija_pokazivaca.end(),
            [](const std::shared_ptr<Polazak> &p1,
               const std::shared_ptr<Polazak> &p2) {
              return VrijemeUMinutama(p1->DajOcekivanoVrijemePolaska()) <
                     VrijemeUMinutama(p2->DajOcekivanoVrijemePolaska());
            });

  std::cout << std::right << std::setw(10) << "Voznja" << std::setw(30)
            << "Odrediste" << std::setw(10) << "Polazak" << std::setw(10)
            << "Dolazak" << std::setw(8) << "Peron" << std::endl;

  std::cout << std::string(70, '-') << std::endl;

  for (const auto &p : kopija_pokazivaca)
    p->Ispisi();
}

int main() {
  try {
    Polasci red_voznje;

    red_voznje.RegistrirajPolazak("Bihac", "CTS 109", 5, 7, 30, 460);
    red_voznje.RegistrirajPolazak("Mostar", "APM 314", 2, 14, 10, 150);

    std::shared_ptr<Polazak> p =
        std::make_shared<Polazak>("Sarajevo", "SMT 291", 12, 15, 35, 45);
    red_voznje.RegistrirajPolazak(p);

    red_voznje.DajPrviPolazak().PostaviKasnjenje(15);
    red_voznje.DajPosljednjiPolazak().PostaviKasnjenje(20);

    red_voznje.Ispisi();

    Polasci kopija(red_voznje);
    Polasci premjesteni(std::move(kopija));

    Polasci dodjela;
    dodjela = red_voznje;

    Polasci move_dodjela;
    move_dodjela = std::move(premjesteni);

    std::cout << "\nBroj polazaka koji kasne: "
              << red_voznje.DajBrojPolazakaKojiKasne() << std::endl;
  } catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
