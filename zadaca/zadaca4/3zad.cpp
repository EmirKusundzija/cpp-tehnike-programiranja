// TP 2025/2026: Zadaća 4, Zadatak 3
#include <algorithm>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>


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
  int max_broj_polazaka, broj_polazaka;
  Polazak **polasci;

  static int ProvjeriKapacitet(int max_broj_polazaka) {
    if (max_broj_polazaka < 0)
      throw std::domain_error("Neispravan broj polazaka");

    return max_broj_polazaka;
  }

  static void Dealociraj(Polazak **polasci, int broj_polazaka) {
    if (polasci == nullptr)
      return;

    for (int i = 0; i < broj_polazaka; i++)
      delete polasci[i];

    delete[] polasci;
  }

  static Polazak **AlocirajIKopiraj(Polazak **izvor, int kapacitet,
                                    int broj_polazaka) {

    if (kapacitet == 0)
      return nullptr;

    Polazak **novi = new Polazak *[kapacitet] {};
    int kopirano = 0;

    try {
      for (; kopirano < broj_polazaka; kopirano++)
        novi[kopirano] = new Polazak(*izvor[kopirano]);
    } catch (...) {
      Dealociraj(novi, kopirano);
      throw;
    }

    return novi;
  }

  static int VrijemeUMinutama(std::pair<int, int> vrijeme) {
    return vrijeme.first * 60 + vrijeme.second;
  }

public:
  explicit Polasci(int max_broj_polazaka);
  Polasci(std::initializer_list<Polazak> lista_polazaka);

  ~Polasci() { Dealociraj(polasci, broj_polazaka); }

  Polasci(const Polasci &p);
  Polasci(Polasci &&p);

  Polasci &operator=(const Polasci &p);
  Polasci &operator=(Polasci &&p);

  void RegistrirajPolazak(std::string_view odrediste,
                          std::string_view oznaka_voznje, int broj_perona,
                          int sat_polaska, int minute_polaska,
                          int trajanje_voznje);

  void RegistrirajPolazak(Polazak *p);

  int DajBrojPolazaka() const { return broj_polazaka; }
  int DajBrojPolazakaKojiKasne() const;

  Polazak &DajPrviPolazak();
  Polazak DajPrviPolazak() const;

  Polazak &DajPosljednjiPolazak();
  Polazak DajPosljednjiPolazak() const;

  void Ispisi() const;
  void IsprazniKolekciju();
};

Polasci::Polasci(int max_broj_polazaka)
    : max_broj_polazaka(ProvjeriKapacitet(max_broj_polazaka)), broj_polazaka(0),
      polasci(max_broj_polazaka == 0 ? nullptr
                                     : new Polazak *[max_broj_polazaka] {}) {}

Polasci::Polasci(std::initializer_list<Polazak> lista_polazaka)
    : max_broj_polazaka(static_cast<int>(lista_polazaka.size())),
      broj_polazaka(0), polasci(lista_polazaka.size() == 0
                                    ? nullptr
                                    : new Polazak *[lista_polazaka.size()] {}) {

  try {
    for (const Polazak &p : lista_polazaka) {
      polasci[broj_polazaka] = new Polazak(p);
      broj_polazaka++;
    }
  } catch (...) {
    Dealociraj(polasci, broj_polazaka);
    throw;
  }
}

Polasci::Polasci(const Polasci &p)
    : max_broj_polazaka(p.max_broj_polazaka), broj_polazaka(p.broj_polazaka),
      polasci(
          AlocirajIKopiraj(p.polasci, p.max_broj_polazaka, p.broj_polazaka)) {}

Polasci::Polasci(Polasci &&p)
    : max_broj_polazaka(p.max_broj_polazaka), broj_polazaka(p.broj_polazaka),
      polasci(p.polasci) {

  p.max_broj_polazaka = 0;
  p.broj_polazaka = 0;
  p.polasci = nullptr;
}

Polasci &Polasci::operator=(const Polasci &p) {
  if (this != &p) {
    Polazak **novi =
        AlocirajIKopiraj(p.polasci, p.max_broj_polazaka, p.broj_polazaka);

    Dealociraj(polasci, broj_polazaka);

    max_broj_polazaka = p.max_broj_polazaka;
    broj_polazaka = p.broj_polazaka;
    polasci = novi;
  }

  return *this;
}

Polasci &Polasci::operator=(Polasci &&p) {
  if (this != &p) {
    Dealociraj(polasci, broj_polazaka);

    max_broj_polazaka = p.max_broj_polazaka;
    broj_polazaka = p.broj_polazaka;
    polasci = p.polasci;

    p.max_broj_polazaka = 0;
    p.broj_polazaka = 0;
    p.polasci = nullptr;
  }

  return *this;
}

void Polasci::RegistrirajPolazak(std::string_view odrediste,
                                 std::string_view oznaka_voznje,
                                 int broj_perona, int sat_polaska,
                                 int minute_polaska, int trajanje_voznje) {

  if (broj_polazaka >= max_broj_polazaka)
    throw std::range_error("Dostignut maksimalni broj polazaka");

  Polazak *novi = new Polazak(odrediste, oznaka_voznje, broj_perona,
                              sat_polaska, minute_polaska, trajanje_voznje);

  polasci[broj_polazaka] = novi;
  broj_polazaka++;
}

void Polasci::RegistrirajPolazak(Polazak *p) {
  if (broj_polazaka >= max_broj_polazaka)
    throw std::range_error("Dostignut maksimalni broj polazaka");

  if (p == nullptr)
    throw std::domain_error("Neispravan polazak");

  Polazak *novi = new Polazak(*p);

  polasci[broj_polazaka] = novi;
  broj_polazaka++;
}

int Polasci::DajBrojPolazakaKojiKasne() const {
  return std::count_if(polasci, polasci + broj_polazaka,
                       [](Polazak *p) { return p->DaLiKasni(); });
}

Polazak &Polasci::DajPrviPolazak() {
  if (broj_polazaka == 0)
    throw std::domain_error("Nema registriranih polazaka");

  return **std::min_element(
      polasci, polasci + broj_polazaka, [](Polazak *p1, Polazak *p2) {
        return VrijemeUMinutama(p1->DajOcekivanoVrijemePolaska()) <
               VrijemeUMinutama(p2->DajOcekivanoVrijemePolaska());
      });
}

Polazak Polasci::DajPrviPolazak() const {
  if (broj_polazaka == 0)
    throw std::domain_error("Nema registriranih polazaka");

  return **std::min_element(
      polasci, polasci + broj_polazaka, [](Polazak *p1, Polazak *p2) {
        return VrijemeUMinutama(p1->DajOcekivanoVrijemePolaska()) <
               VrijemeUMinutama(p2->DajOcekivanoVrijemePolaska());
      });
}

Polazak &Polasci::DajPosljednjiPolazak() {
  if (broj_polazaka == 0)
    throw std::domain_error("Nema registriranih polazaka");

  return **std::max_element(
      polasci, polasci + broj_polazaka, [](Polazak *p1, Polazak *p2) {
        return VrijemeUMinutama(p1->DajOcekivanoVrijemePolaska()) <
               VrijemeUMinutama(p2->DajOcekivanoVrijemePolaska());
      });
}

Polazak Polasci::DajPosljednjiPolazak() const {
  if (broj_polazaka == 0)
    throw std::domain_error("Nema registriranih polazaka");

  return **std::max_element(
      polasci, polasci + broj_polazaka, [](Polazak *p1, Polazak *p2) {
        return VrijemeUMinutama(p1->DajOcekivanoVrijemePolaska()) <
               VrijemeUMinutama(p2->DajOcekivanoVrijemePolaska());
      });
}

void Polasci::Ispisi() const {
  if (broj_polazaka == 0)
    return;

  Polazak **kopija_pokazivaca = new Polazak *[broj_polazaka];

  try {
    std::copy(polasci, polasci + broj_polazaka, kopija_pokazivaca);

    std::sort(kopija_pokazivaca, kopija_pokazivaca + broj_polazaka,
              [](Polazak *p1, Polazak *p2) {
                return VrijemeUMinutama(p1->DajOcekivanoVrijemePolaska()) <
                       VrijemeUMinutama(p2->DajOcekivanoVrijemePolaska());
              });

    std::cout << std::right << std::setw(10) << "Voznja" << std::setw(30)
              << "Odrediste" << std::setw(10) << "Polazak" << std::setw(10)
              << "Dolazak" << std::setw(8) << "Peron" << std::endl;

    std::cout << std::string(70, '-') << std::endl;

    for (int i = 0; i < broj_polazaka; i++)
      kopija_pokazivaca[i]->Ispisi();

    delete[] kopija_pokazivaca;
  } catch (...) {
    delete[] kopija_pokazivaca;
    throw;
  }
}

void Polasci::IsprazniKolekciju() {
  for (int i = 0; i < broj_polazaka; i++) {
    delete polasci[i];
    polasci[i] = nullptr;
  }

  broj_polazaka = 0;
}

int main() {
  try {
    Polasci red_voznje(3);

    red_voznje.RegistrirajPolazak("Bihac", "CTS 109", 5, 7, 30, 460);
    red_voznje.RegistrirajPolazak("Mostar", "APM 314", 2, 14, 10, 150);
    red_voznje.RegistrirajPolazak("Sarajevo", "SMT 291", 12, 15, 35, 45);

    red_voznje.DajPrviPolazak().PostaviKasnjenje(15);
    red_voznje.DajPosljednjiPolazak().PostaviKasnjenje(20);

    std::cout << "Original:\n";
    red_voznje.Ispisi();

    std::cout << "\nKopirajuci konstruktor:\n";
    Polasci kopija(red_voznje);
    kopija.Ispisi();

    std::cout << "\nPomjerajuci konstruktor:\n";
    Polasci premjesteni(std::move(kopija));
    premjesteni.Ispisi();

    std::cout << "\nKopirajuci operator dodjele:\n";
    Polasci dodjela(1);
    dodjela = red_voznje;
    dodjela.Ispisi();

    std::cout << "\nPomjerajuci operator dodjele:\n";
    Polasci move_dodjela(1);
    move_dodjela = std::move(premjesteni);
    move_dodjela.Ispisi();

    std::cout << "\nBroj polazaka koji kasne: "
              << red_voznje.DajBrojPolazakaKojiKasne() << std::endl;

    std::cout << "\nPraznjenje kolekcije:\n";
    red_voznje.IsprazniKolekciju();
    std::cout << "Broj polazaka nakon praznjenja: "
              << red_voznje.DajBrojPolazaka() << std::endl;

  } catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
