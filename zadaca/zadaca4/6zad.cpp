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
  bool video_traka_ili_dvd;
  std::string naziv_filma;
  std::string zanr;
  int godina_produkcije;
  Korisnik *pok_na_korisnika;

public:
  Film(int evidencijski_broj, bool video_traka_ili_dvd, std::string naziv_filma,
       std::string zanr, int godina_produkcije)
      : evidencijski_broj(evidencijski_broj),
        video_traka_ili_dvd(video_traka_ili_dvd),
        naziv_filma(std::move(naziv_filma)), zanr(std::move(zanr)),
        godina_produkcije(godina_produkcije), pok_na_korisnika(nullptr) {}

  int DajEvidencijskiBroj() const { return evidencijski_broj; }
  std::string DajNaziv() const { return naziv_filma; }
  std::string DajZanr() const { return zanr; }
  int DajGodinuProdukcije() const { return godina_produkcije; }
  bool DaLiJeDVD() const { return video_traka_ili_dvd; }

  void ZaduziFilm(Korisnik &k) { pok_na_korisnika = &k; }
  void RazduziFilm() { pok_na_korisnika = nullptr; }
  bool DaLiJeZaduzen() const { return pok_na_korisnika != nullptr; }

  Korisnik &DajKodKogaJe() const {
    if (!pok_na_korisnika)
      throw std::domain_error("Film nije zaduzen");
    return *pok_na_korisnika;
  }

  Korisnik *DajPokKodKogaJe() const { return pok_na_korisnika; }

  void Ispisi() const {
    std::cout << "Evidencijski broj: " << evidencijski_broj << "\n";
    std::cout << "Medij: " << (DaLiJeDVD() ? "DVD" : "Video traka") << "\n";
    std::cout << "Naziv filma: " << naziv_filma << "\n";
    std::cout << "Zanr: " << zanr << "\n";
    std::cout << "Godina produkcije: " << godina_produkcije << "\n";
  }
};

class Videoteka {
  std::map<int, std::unique_ptr<Korisnik>> mapa_korisnika;
  std::map<int, std::unique_ptr<Film>> mapa_filmova;

  void KopirajIz(const Videoteka &v) {
    for (const auto &par : v.mapa_korisnika) {
      mapa_korisnika.emplace(par.first,
                             std::make_unique<Korisnik>(*par.second));
    }

    for (const auto &par : v.mapa_filmova) {
      const Film *stari = par.second.get();

      mapa_filmova.emplace(
          par.first, std::make_unique<Film>(stari->DajEvidencijskiBroj(),
                                            stari->DaLiJeDVD(),
                                            stari->DajNaziv(), stari->DajZanr(),
                                            stari->DajGodinuProdukcije()));
    }

    for (const auto &par : v.mapa_filmova) {
      const Film *stari_film = par.second.get();

      if (stari_film->DaLiJeZaduzen()) {
        int clanski_broj = stari_film->DajKodKogaJe().DajClanskiBroj();

        mapa_filmova.at(par.first)->ZaduziFilm(
            *mapa_korisnika.at(clanski_broj));
      }
    }
  }

public:
  Videoteka() = default;
  ~Videoteka() = default;

  Videoteka(const Videoteka &v) { KopirajIz(v); }

  Videoteka(Videoteka &&v) noexcept
      : mapa_korisnika(std::move(v.mapa_korisnika)),
        mapa_filmova(std::move(v.mapa_filmova)) {}

  Videoteka &operator=(const Videoteka &v) {
    if (this != &v) {
      Videoteka kopija(v);
      mapa_korisnika.swap(kopija.mapa_korisnika);
      mapa_filmova.swap(kopija.mapa_filmova);
    }

    return *this;
  }

  Videoteka &operator=(Videoteka &&v) noexcept {
    if (this != &v) {
      mapa_korisnika = std::move(v.mapa_korisnika);
      mapa_filmova = std::move(v.mapa_filmova);
    }

    return *this;
  }

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

  void RegistrirajNoviFilm(int evidencijski_broj, bool video_traka_ili_dvd,
                           std::string naziv_filma, std::string zanr,
                           int godina_produkcije) {
    if (mapa_filmova.count(evidencijski_broj))
      throw std::logic_error("Film s tim evidencijskim brojem vec postoji");

    mapa_filmova.emplace(
        evidencijski_broj,
        std::make_unique<Film>(evidencijski_broj, video_traka_ili_dvd,
                               std::move(naziv_filma), std::move(zanr),
                               godina_produkcije));
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
        const Korisnik &k = par.second->DajKodKogaJe();

        std::cout << "Zaduzen kod korisnika: " << k.DajImeIPrezime() << " ("
                  << k.DajClanskiBroj() << ")\n";
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
      if (par.second->DajPokKodKogaJe() == it_korisnik->second.get()) {
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
    std::cout << "\nOdaberite opciju:\n"
              << "1 - Registriraj novog korisnika\n"
              << "2 - Registriraj novi film\n"
              << "3 - Nadji korisnika\n"
              << "4 - Nadji film\n"
              << "5 - Izlistaj korisnike\n"
              << "6 - Izlistaj filmove\n"
              << "7 - Zaduzi film\n"
              << "8 - Razduzi film\n"
              << "9 - Prikazi zaduzenja korisnika\n"
              << "0 - Kraj\n"
              << "Opcija: ";

    int opcija;
    if (!(std::cin >> opcija))
      break;

    try {
      if (opcija == 0)
        break;

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

        std::cout << "Korisnik je registriran.\n";
      } else if (opcija == 2) {
        int evidencijski_broj, godina;
        char medij;
        std::string naziv, zanr;

        std::cout << "Evidencijski broj: ";
        std::cin >> evidencijski_broj;

        std::cout << "Medij (D za DVD, V za video traku): ";
        std::cin >> medij;
        std::cin.ignore(10000, '\n');

        std::cout << "Naziv filma: ";
        std::getline(std::cin, naziv);

        std::cout << "Zanr: ";
        std::getline(std::cin, zanr);

        std::cout << "Godina produkcije: ";
        std::cin >> godina;

        bool dvd = (medij == 'D' || medij == 'd');

        videoteka.RegistrirajNoviFilm(evidencijski_broj, dvd, naziv, zanr,
                                      godina);

        std::cout << "Film je registriran.\n";
      } else if (opcija == 3) {
        int clanski_broj;

        std::cout << "Clanski broj: ";
        std::cin >> clanski_broj;

        videoteka.NadjiKorisnika(clanski_broj).Ispisi();
      } else if (opcija == 4) {
        int evidencijski_broj;

        std::cout << "Evidencijski broj: ";
        std::cin >> evidencijski_broj;

        Film &f = videoteka.NadjiFilm(evidencijski_broj);
        f.Ispisi();

        if (f.DaLiJeZaduzen()) {
          Korisnik &k = f.DajKodKogaJe();

          std::cout << "Zaduzen kod korisnika: " << k.DajImeIPrezime() << " ("
                    << k.DajClanskiBroj() << ")\n";
        }
      } else if (opcija == 5) {
        videoteka.IzlistajKorisnike();
      } else if (opcija == 6) {
        videoteka.IzlistajFilmove();
      } else if (opcija == 7) {
        int evidencijski_broj, clanski_broj;

        std::cout << "Evidencijski broj filma: ";
        std::cin >> evidencijski_broj;

        std::cout << "Clanski broj korisnika: ";
        std::cin >> clanski_broj;

        videoteka.ZaduziFilm(evidencijski_broj, clanski_broj);

        std::cout << "Film je zaduzen.\n";
      } else if (opcija == 8) {
        int evidencijski_broj;

        std::cout << "Evidencijski broj filma: ";
        std::cin >> evidencijski_broj;

        videoteka.RazduziFilm(evidencijski_broj);

        std::cout << "Film je razduzen.\n";
      } else if (opcija == 9) {
        int clanski_broj;

        std::cout << "Clanski broj korisnika: ";
        std::cin >> clanski_broj;

        videoteka.PrikaziZaduzenja(clanski_broj);
      } else {
        std::cout << "Nepoznata opcija.\n";
      }
    } catch (const std::exception &e) {
      std::cout << "Izuzetak: " << e.what() << "\n";
    }
  }

  return 0;
}
