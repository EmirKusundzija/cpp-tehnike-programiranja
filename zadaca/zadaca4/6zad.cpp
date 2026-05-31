// TP 2025/2026: Zadaća 4, Zadatak 6
#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

class Korisnik {
  int clanski_broj;
  std::string ime_prezime;
  std::string adresa;
  std::string broj_telefona;

public:
  Korisnik(int clanski_broj, std::string ime_prezime, std::string adresa,
           std::string broj_telefona)
      : clanski_broj(clanski_broj), ime_prezime(std::move(ime_prezime)),
        adresa(std::move(adresa)), broj_telefona(std::move(broj_telefona)) {}

  int DajClanskiBroj() const { return clanski_broj; }
  std::string DajImeIPrezime() const { return ime_prezime; }
  std::string DajAdresu() const { return adresa; }
  std::string DajTelefon() const { return broj_telefona; }

  void Ispisi() const {
    std::cout << "Clanski broj: " << clanski_broj << "\n";
    std::cout << "Ime i prezime: " << ime_prezime << "\n";
    std::cout << "Adresa: " << adresa << "\n";
    std::cout << "Telefon: " << broj_telefona << "\n";
  }
};

class Film {
  int evidencijski_broj;
  bool dvd;
  std::string naziv_filma;
  std::string zanr;
  int godina_produkcije;

  // Film ne posjeduje korisnika; samo pamti kod koga je zaduzen.
  Korisnik *pok_na_korisnika;

public:
  Film(int evidencijski_broj, bool dvd, std::string naziv_filma,
       std::string zanr, int godina_produkcije)
      : evidencijski_broj(evidencijski_broj), dvd(dvd),
        naziv_filma(std::move(naziv_filma)), zanr(std::move(zanr)),
        godina_produkcije(godina_produkcije), pok_na_korisnika(nullptr) {}

  int DajEvidencijskiBroj() const { return evidencijski_broj; }
  std::string DajNaziv() const { return naziv_filma; }
  std::string DajZanr() const { return zanr; }
  int DajGodinuProdukcije() const { return godina_produkcije; }
  bool DaLiJeDVD() const { return dvd; }

  void ZaduziFilm(Korisnik &korisnik) { pok_na_korisnika = &korisnik; }
  void RazduziFilm() { pok_na_korisnika = nullptr; }
  bool DaLiJeZaduzen() const { return pok_na_korisnika != nullptr; }

  Korisnik &DajKodKogaJe() const {
    if (!pok_na_korisnika)
      throw std::domain_error("Film nije zaduzen");
    return *pok_na_korisnika;
  }

  // Naziv koji se koristi u deklaraciji interfejsa i u javnim autotestovima.
  Korisnik *DajPokKogaJe() const { return pok_na_korisnika; }

  // Zadrzana je i varijanta iz tekstualnog opisa zadatka.
  Korisnik *DajPokKodKogaJe() const { return DajPokKogaJe(); }

  void Ispisi() const {
    std::cout << "Evidencijski broj: " << evidencijski_broj << "\n";
    std::cout << "Medij: " << (dvd ? "DVD" : "Video traka") << "\n";
    std::cout << "Naziv filma: " << naziv_filma << "\n";
    std::cout << "Zanr: " << zanr << "\n";
    std::cout << "Godina produkcije: " << godina_produkcije << "\n";
  }
};

class Videoteka {
  std::map<int, std::unique_ptr<Korisnik>> mapa_korisnika;
  std::map<int, std::unique_ptr<Film>> mapa_filmova;

  void KopirajIz(const Videoteka &druga) {
    for (const auto &par : druga.mapa_korisnika)
      mapa_korisnika.emplace(par.first,
                             std::make_unique<Korisnik>(*par.second));

    for (const auto &par : druga.mapa_filmova) {
      const Film &stari = *par.second;
      mapa_filmova.emplace(
          par.first,
          std::make_unique<Film>(stari.DajEvidencijskiBroj(), stari.DaLiJeDVD(),
                                 stari.DajNaziv(), stari.DajZanr(),
                                 stari.DajGodinuProdukcije()));
    }

    for (const auto &par : druga.mapa_filmova) {
      const Film &stari = *par.second;
      if (stari.DaLiJeZaduzen()) {
        int clanski_broj = stari.DajKodKogaJe().DajClanskiBroj();
        mapa_filmova.at(par.first)->ZaduziFilm(
            *mapa_korisnika.at(clanski_broj));
      }
    }
  }

public:
  Videoteka() = default;
  ~Videoteka() = default;

  Videoteka(const Videoteka &druga) { KopirajIz(druga); }
  Videoteka(Videoteka &&druga) noexcept = default;

  Videoteka &operator=(const Videoteka &druga) {
    if (this != &druga) {
      Videoteka kopija(druga);
      mapa_korisnika.swap(kopija.mapa_korisnika);
      mapa_filmova.swap(kopija.mapa_filmova);
    }
    return *this;
  }

  Videoteka &operator=(Videoteka &&druga) noexcept = default;

  void RegistrirajNovogKorisnika(int clanski_broj, std::string ime_prezime,
                                 std::string adresa,
                                 std::string broj_telefona) {
    if (mapa_korisnika.count(clanski_broj))
      throw std::logic_error("Vec postoji korisnik s tim clanskim brojem");

    mapa_korisnika.emplace(clanski_broj,
                           std::make_unique<Korisnik>(
                               clanski_broj, std::move(ime_prezime),
                               std::move(adresa), std::move(broj_telefona)));
  }

  void RegistrirajNoviFilm(int evidencijski_broj, bool dvd,
                           std::string naziv_filma, std::string zanr,
                           int godina_produkcije) {
    if (mapa_filmova.count(evidencijski_broj))
      throw std::logic_error("Film s tim evidencijskim brojem vec postoji");

    mapa_filmova.emplace(
        evidencijski_broj,
        std::make_unique<Film>(evidencijski_broj, dvd, std::move(naziv_filma),
                               std::move(zanr), godina_produkcije));
  }

  Korisnik &NadjiKorisnika(int clanski_broj) {
    auto it = mapa_korisnika.find(clanski_broj);
    if (it == mapa_korisnika.end())
      throw std::logic_error("Korisnik nije nadjen");
    return *it->second;
  }

  const Korisnik &NadjiKorisnika(int clanski_broj) const {
    auto it = mapa_korisnika.find(clanski_broj);
    if (it == mapa_korisnika.end())
      throw std::logic_error("Korisnik nije nadjen");
    return *it->second;
  }

  Film &NadjiFilm(int evidencijski_broj) {
    auto it = mapa_filmova.find(evidencijski_broj);
    if (it == mapa_filmova.end())
      throw std::logic_error("Film nije nadjen");
    return *it->second;
  }

  const Film &NadjiFilm(int evidencijski_broj) const {
    auto it = mapa_filmova.find(evidencijski_broj);
    if (it == mapa_filmova.end())
      throw std::logic_error("Film nije nadjen");
    return *it->second;
  }

  void IzlistajKorisnike() const {
    bool prvi = true;
    for (const auto &par : mapa_korisnika) {
      if (!prvi)
        std::cout << "\n";
      par.second->Ispisi();
      prvi = false;
    }
  }

  void IzlistajFilmove() const {
    bool prvi = true;
    for (const auto &par : mapa_filmova) {
      if (!prvi)
        std::cout << "\n";
      par.second->Ispisi();
      if (par.second->DaLiJeZaduzen()) {
        const Korisnik &korisnik = par.second->DajKodKogaJe();
        std::cout << "Zaduzen kod korisnika: " << korisnik.DajImeIPrezime()
                  << " (" << korisnik.DajClanskiBroj() << ")\n";
      }
      prvi = false;
    }
  }

  void ZaduziFilm(int evidencijski_broj, int clanski_broj) {
    auto it_film = mapa_filmova.find(evidencijski_broj);
    if (it_film == mapa_filmova.end())
      throw std::logic_error("Film nije nadjen");

    auto it_korisnik = mapa_korisnika.find(clanski_broj);
    if (it_korisnik == mapa_korisnika.end())
      throw std::logic_error("Korisnik nije nadjen");

    if (it_film->second->DaLiJeZaduzen())
      throw std::logic_error("Film vec zaduzen");
    it_film->second->ZaduziFilm(*it_korisnik->second);
  }

  void RazduziFilm(int evidencijski_broj) {
    auto it = mapa_filmova.find(evidencijski_broj);
    if (it == mapa_filmova.end())
      throw std::logic_error("Film nije nadjen");
    if (!it->second->DaLiJeZaduzen())
      throw std::logic_error("Film nije zaduzen");
    it->second->RazduziFilm();
  }

  void PrikaziZaduzenja(int clanski_broj) const {
    auto it_korisnik = mapa_korisnika.find(clanski_broj);
    if (it_korisnik == mapa_korisnika.end())
      throw std::logic_error("Korisnik nije nadjen");

    bool ima_zaduzenja = false;
    for (const auto &par : mapa_filmova) {
      if (par.second->DajPokKogaJe() == it_korisnik->second.get()) {
        if (ima_zaduzenja)
          std::cout << "\n";
        par.second->Ispisi();
        ima_zaduzenja = true;
      }
    }

    if (!ima_zaduzenja)
      std::cout << "Korisnik nema zaduzenja!\n";
  }
};

int main() {
  Videoteka videoteka;

  for (;;) {
    std::cout << "=== VIDEOTEKA ===\n"
              << "1. Registruj novog korisnika\n"
              << "2. Registruj novi film\n"
              << "3. Izlistaj sve korisnike\n"
              << "4. Izlistaj sve filmove\n"
              << "5. Zaduzi film korisniku\n"
              << "6. Razduzi film\n"
              << "7. Prikazi zaduzenja korisnika\n"
              << "0. Izlaz\n"
              << "Opcija: ";

    int opcija;
    if (!(std::cin >> opcija) || opcija == 0)
      break;

    try {
      if (opcija == 1) {
        int clanski_broj;
        std::string ime_prezime, adresa, telefon;

        std::cout << "Clanski broj: ";
        std::cin >> clanski_broj;
        std::cin.ignore(10000, '\n');
        std::cout << "Ime i prezime: ";
        std::getline(std::cin, ime_prezime);
        std::cout << "Adresa: ";
        std::getline(std::cin, adresa);
        std::cout << "Telefon: ";
        std::getline(std::cin, telefon);

        videoteka.RegistrirajNovogKorisnika(clanski_broj, ime_prezime, adresa,
                                            telefon);
        std::cout << "Korisnik uspjesno registrovan.\n";
      } else if (opcija == 2) {
        int evidencijski_broj, godina_produkcije;
        char odgovor;
        std::string naziv_filma, zanr;

        std::cout << "Evidencijski broj: ";
        std::cin >> evidencijski_broj;
        std::cout << "DVD (d/n): ";
        std::cin >> odgovor;
        std::cin.ignore(10000, '\n');
        std::cout << "Naziv filma: ";
        std::getline(std::cin, naziv_filma);
        std::cout << "Zanr: ";
        std::getline(std::cin, zanr);
        std::cout << "Godina produkcije: ";
        std::cin >> godina_produkcije;

        bool dvd = odgovor == 'd' || odgovor == 'D';
        videoteka.RegistrirajNoviFilm(evidencijski_broj, dvd, naziv_filma, zanr,
                                      godina_produkcije);
        std::cout << "Film uspjesno registrovan.\n";
      } else if (opcija == 3) {
        videoteka.IzlistajKorisnike();
      } else if (opcija == 4) {
        videoteka.IzlistajFilmove();
      } else if (opcija == 5) {
        int evidencijski_broj, clanski_broj;
        std::cout << "Evidencijski broj filma: ";
        std::cin >> evidencijski_broj;
        std::cout << "Clanski broj korisnika: ";
        std::cin >> clanski_broj;
        videoteka.ZaduziFilm(evidencijski_broj, clanski_broj);
        std::cout << "Film uspjesno zaduzen.\n";
      } else if (opcija == 6) {
        int evidencijski_broj;
        std::cout << "Evidencijski broj filma: ";
        std::cin >> evidencijski_broj;
        videoteka.RazduziFilm(evidencijski_broj);
        std::cout << "Film uspjesno razduzen.\n";
      } else if (opcija == 7) {
        int clanski_broj;
        std::cout << "Clanski broj korisnika: ";
        std::cin >> clanski_broj;
        videoteka.PrikaziZaduzenja(clanski_broj);
      } else {
        std::cout << "Nepoznata opcija.\n";
      }
    } catch (const std::exception &e) {
      std::cout << e.what() << "\n";
    }

    std::cout << "\n";
  }

  return 0;
}