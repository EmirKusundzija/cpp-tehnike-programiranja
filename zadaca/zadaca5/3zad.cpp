// TP 2025/2026: Zadaća 5, Zadatak 3
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

class Narudzba {
  std::string naziv_obroka;
  double cijena_obroka;
  std::string ime_prezime;

public:
  Narudzba(std::string_view naziv_obroka, double cijena_obroka,
           std::string_view ime_prezime)
      : naziv_obroka(naziv_obroka), cijena_obroka(cijena_obroka),
        ime_prezime(ime_prezime) {}

  std::string_view DajNazivObroka() const { return naziv_obroka; }
  double DajCijenuObroka() const { return cijena_obroka; }
  std::string_view DajNarucioca() const { return ime_prezime; }

  virtual double DajUkupnuCijenu() const { return cijena_obroka; }

  virtual void Ispisi() const {
    std::cout << "Obrok: " << naziv_obroka << '\n'
              << "Cijena: " << cijena_obroka << " KM\n"
              << "Narucilac: " << ime_prezime << '\n';
  }

  virtual Narudzba *DajKopiju() const { return new Narudzba(*this); }

  virtual ~Narudzba() = default;
};

class NarudzbaSaPicem : public Narudzba {
  std::string naziv_pica;
  double cijena_pica;

public:
  NarudzbaSaPicem(std::string_view naziv_obroka, double cijena_obroka,
                  std::string_view ime_prezime, std::string_view naziv_pica,
                  double cijena_pica)
      : Narudzba(naziv_obroka, cijena_obroka, ime_prezime),
        naziv_pica(naziv_pica), cijena_pica(cijena_pica) {}

  std::string_view DajNazivPica() const { return naziv_pica; }
  double DajCijenuPica() const { return cijena_pica; }

  double DajUkupnuCijenu() const override {
    return DajCijenuObroka() + cijena_pica;
  }

  void Ispisi() const override {
    std::cout << "Obrok: " << DajNazivObroka() << '\n'
              << "Pice: " << naziv_pica << '\n'
              << "Cijena: " << DajCijenuObroka() << " KM\n"
              << "Cijena pica: " << cijena_pica << " KM\n"
              << "Ukupna cijena: " << DajUkupnuCijenu() << " KM\n"
              << "Narucilac: " << DajNarucioca() << '\n';
  }

  Narudzba *DajKopiju() const override { return new NarudzbaSaPicem(*this); }
};

class Narudzbe {
  std::vector<Narudzba *> narudzbe;

  static void UkloniCR(std::string &red) {
    if (!red.empty() && red.back() == '\r')
      red.pop_back();
  }

  static double ProcitajCijenu(const std::string &red) {
    std::istringstream tok(red);
    double cijena;

    if (!(tok >> cijena))
      throw std::logic_error("Problemi pri citanju");

    tok >> std::ws;
    if (!tok.eof() || !std::isfinite(cijena) || cijena < 0)
      throw std::logic_error("Problemi pri citanju");

    return cijena;
  }

  static double NadjiCijenu(const std::map<std::string, double> &cjenovnik,
                            const std::string &naziv) {
    auto it = cjenovnik.find(naziv);
    if (it == cjenovnik.end())
      throw std::logic_error("Nema odgovarajuce cijene");
    return it->second;
  }

  static std::vector<Narudzba *>
  KopirajNarudzbe(const std::vector<Narudzba *> &izvor) {
    std::vector<Narudzba *> kopije;

    try {
      kopije.reserve(izvor.size());
      for (const auto *narudzba : izvor)
        kopije.push_back(narudzba->DajKopiju());
    } catch (...) {
      for (auto *narudzba : kopije)
        delete narudzba;
      throw;
    }

    return kopije;
  }

  void Ocisti() noexcept {
    for (auto *narudzba : narudzbe)
      delete narudzba;
    narudzbe.clear();
  }

  void DodajNarudzbu(Narudzba *nova_narudzba) {
    try {
      narudzbe.push_back(nova_narudzba);
    } catch (...) {
      delete nova_narudzba;
      throw;
    }
  }

public:
  Narudzbe() = default;

  ~Narudzbe() { Ocisti(); }

  Narudzbe(const Narudzbe &druge) : narudzbe(KopirajNarudzbe(druge.narudzbe)) {}

  Narudzbe(Narudzbe &&druge) noexcept { std::swap(narudzbe, druge.narudzbe); }

  Narudzbe &operator=(const Narudzbe &druge) {
    if (this != &druge) {
      Narudzbe kopija(druge);
      std::swap(narudzbe, kopija.narudzbe);
    }
    return *this;
  }

  Narudzbe &operator=(Narudzbe &&druge) noexcept {
    if (this != &druge)
      std::swap(narudzbe, druge.narudzbe);
    return *this;
  }

  void NaruciObrok(std::string_view naziv_obroka, double cijena_obroka,
                   std::string_view ime_prezime) {
    DodajNarudzbu(new Narudzba(naziv_obroka, cijena_obroka, ime_prezime));
  }

  void NaruciObrokSaPicem(std::string_view naziv_obroka, double cijena_obroka,
                          std::string_view ime_prezime,
                          std::string_view naziv_pica, double cijena_pica) {
    DodajNarudzbu(new NarudzbaSaPicem(naziv_obroka, cijena_obroka, ime_prezime,
                                      naziv_pica, cijena_pica));
  }

  void ObradiNaruzdbu() {
    if (narudzbe.empty())
      throw std::range_error("Nema vise narudzbi");

    narudzbe.front()->Ispisi();
    delete narudzbe.front();
    narudzbe.erase(narudzbe.begin());
  }

  void ObradiNarudzbu() { ObradiNaruzdbu(); }

  bool DaLiImaNarudzbi() const { return !narudzbe.empty(); }

  double operator[](std::string_view ime_prezime) const {
    double ukupno = 0;

    for (const auto *narudzba : narudzbe)
      if (narudzba->DajNarucioca() == ime_prezime)
        ukupno += narudzba->DajUkupnuCijenu();

    return ukupno;
  }

  void UcitajIzDatoteka(std::string_view ime_datoteke_narudzbi,
                        std::string_view ime_datoteke_cijena) {
    std::ifstream datoteka_narudzbi{std::string(ime_datoteke_narudzbi)};
    std::ifstream datoteka_cijena{std::string(ime_datoteke_cijena)};

    if (!datoteka_narudzbi || !datoteka_cijena)
      throw std::logic_error("Trazena datoteka ne postoji");

    std::map<std::string, double> cjenovnik;
    std::string naziv, red_cijene;

    while (std::getline(datoteka_cijena, naziv)) {
      UkloniCR(naziv);

      if (!std::getline(datoteka_cijena, red_cijene))
        throw std::logic_error("Problemi pri citanju");

      UkloniCR(red_cijene);

      if (naziv.empty())
        throw std::logic_error("Problemi pri citanju");

      cjenovnik[naziv] = ProcitajCijenu(red_cijene);
    }

    if (datoteka_cijena.bad())
      throw std::logic_error("Problemi pri citanju");

    Narudzbe nove_narudzbe;
    std::string ime_prezime, naziv_obroka, naziv_pica;

    while (std::getline(datoteka_narudzbi, ime_prezime)) {
      UkloniCR(ime_prezime);

      if (!std::getline(datoteka_narudzbi, naziv_obroka) ||
          !std::getline(datoteka_narudzbi, naziv_pica))
        throw std::logic_error("Problemi pri citanju");

      UkloniCR(naziv_obroka);
      UkloniCR(naziv_pica);

      if (ime_prezime.empty() || naziv_obroka.empty())
        throw std::logic_error("Problemi pri citanju");

      const double cijena_obroka = NadjiCijenu(cjenovnik, naziv_obroka);

      if (naziv_pica.empty()) {
        nove_narudzbe.NaruciObrok(naziv_obroka, cijena_obroka, ime_prezime);
      } else {
        const double cijena_pica = NadjiCijenu(cjenovnik, naziv_pica);
        nove_narudzbe.NaruciObrokSaPicem(naziv_obroka, cijena_obroka,
                                         ime_prezime, naziv_pica, cijena_pica);
      }
    }

    if (datoteka_narudzbi.bad())
      throw std::logic_error("Problemi pri citanju");

    narudzbe.reserve(narudzbe.size() + nove_narudzbe.narudzbe.size());
    narudzbe.insert(narudzbe.end(), nove_narudzbe.narudzbe.begin(),
                    nove_narudzbe.narudzbe.end());
    nove_narudzbe.narudzbe.clear();
  }
};

int main() {
  try {
    Narudzbe narudzbe;

    narudzbe.NaruciObrok("Burek", 4, "Donald Trump");
    narudzbe.NaruciObrokSaPicem("Sogan dolma", 4, "Josip Broz Tito", "Fanta",
                                2.5);

    std::cout << "Ukupno za Josipa: " << narudzbe["Josip Broz Tito"]
              << " KM\n\n";

    Narudzbe kopija(narudzbe);
    kopija.ObradiNaruzdbu();

    std::cout << "\nOriginal i dalje sadrzi obje narudzbe:\n";
    while (narudzbe.DaLiImaNarudzbi()) {
      narudzbe.ObradiNaruzdbu();
      std::cout << '\n';
    }

    Narudzbe ucitane;
    ucitane.UcitajIzDatoteka("NARUDZBE.TXT", "CJENOVNIK.TXT");
    while (ucitane.DaLiImaNarudzbi())
      ucitane.ObradiNaruzdbu();
  } catch (const std::exception &e) {
    std::cout << e.what() << '\n';
  }

  return 0;
}
