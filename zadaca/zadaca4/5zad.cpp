// TP 2025/2026: Zadaća 4, Zadatak 5
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <utility>

class Korisnik {
  int clanski_broj;
  std::string ime_prezime;
  std::string adresa;
  std::string broj_telefona;

public:
  Korisnik(int CB, std::string IP, std::string Adresa, std::string BT)
      : clanski_broj(CB), ime_prezime(IP), adresa(Adresa), broj_telefona(BT) {}

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
  bool video_traka_ili_dvd; // DVD ako je true, false ako je Video traka
  std::string naziv_filma;
  std::string zanr;
  int godina_produkcije;
  Korisnik *pok_na_korisnika;

public:
  Film(int EB, bool VTDVD, std::string NF, std::string Z, int GP)
      : evidencijski_broj(EB), video_traka_ili_dvd(VTDVD), naziv_filma(NF),
        zanr(Z), godina_produkcije(GP), pok_na_korisnika(nullptr) {};

  int DajEvidencijskiBroj() const { return evidencijski_broj; }
  std::string DajNaziv() const { return naziv_filma; }
  std::string DajZanr() const { return zanr; }
  int DajGodinuProdukcije() const { return godina_produkcije; }
  bool DaLiJeDVD() const { return video_traka_ili_dvd; }

  void ZaduziFilm(Korisnik &k) { pok_na_korisnika = &k; }
  void RazduziFilm() { pok_na_korisnika = nullptr; }
  bool DaLiJeZaduzen() const { return pok_na_korisnika != nullptr; }
  Korisnik &DajKodKogaJe() const {
    if (pok_na_korisnika == nullptr)
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
  // mapa korisnika
  std::map<int, Korisnik *> mapa_korisnika;
  // mapa filmova
  std::map<int, Film *> mapa_filmova;

  void ObrisiSve() {
    for (auto &par : mapa_korisnika) {
      delete par.second;
    }

    for (auto &par : mapa_filmova) {
      delete par.second;
    }

    mapa_korisnika.clear();
    mapa_filmova.clear();
  }
  void ZamijeniSa(Videoteka &v) noexcept {
    mapa_korisnika.swap(v.mapa_korisnika);
    mapa_filmova.swap(v.mapa_filmova);
  }
  void KopirajIz(const Videoteka &v) {
    try {
      for (const auto &par : v.mapa_korisnika) {
        Korisnik *novi = new Korisnik(*par.second);
        try {
          mapa_korisnika.insert({par.first, novi});
        } catch (...) {
          delete novi;
          throw;
        }
      }

      for (const auto &par : v.mapa_filmova) {
        const Film *stari = par.second;
        Film *novi = new Film(stari->DajEvidencijskiBroj(), stari->DaLiJeDVD(),
                              stari->DajNaziv(), stari->DajZanr(),
                              stari->DajGodinuProdukcije());
        try {
          mapa_filmova.insert({par.first, novi});
        } catch (...) {
          delete novi;
          throw;
        }
      }

      for (const auto &par : v.mapa_filmova) {
        Film *stari_film = par.second;
        if (stari_film->DaLiJeZaduzen()) {
          int clanski_broj = stari_film->DajKodKogaJe().DajClanskiBroj();
          mapa_filmova.at(par.first)->ZaduziFilm(
              *mapa_korisnika.at(clanski_broj));
        }
      }
    } catch (...) {
      ObrisiSve();
      throw;
    }
  }

public:
  Videoteka() = default;

  ~Videoteka() { ObrisiSve(); }

  Videoteka(const Videoteka &v) { KopirajIz(v); }

  Videoteka(Videoteka &&v) noexcept { ZamijeniSa(v); }

  Videoteka &operator=(const Videoteka &v) {
    if (this != &v) {
      Videoteka kopija(v);
      ZamijeniSa(kopija);
    }
    return *this;
  }

  Videoteka &operator=(Videoteka &&v) noexcept {
    if (this != &v) {
      ObrisiSve();
      ZamijeniSa(v);
    }
    return *this;
  }

  void RegistrirajNovogKorisnika(int clanski_broj, std::string ime_prezime,
                                 std::string adresa,
                                 std::string broj_telefona) {
    if (mapa_korisnika.count(clanski_broj))
      throw std::logic_error("Vec postoji korisnik s tim clanskim brojem");

    Korisnik *novi = new Korisnik(clanski_broj, std::move(ime_prezime),
                                  std::move(adresa), std::move(broj_telefona));
    try {
      mapa_korisnika.insert({clanski_broj, novi});
    } catch (...) {
      delete novi;
      throw;
    }
  }

  void RegistrirajNoviFilm(int evidencijski_broj, bool dvd,
                           std::string naziv_filma, std::string zanr,
                           int godina_produkcije) {
    if (mapa_filmova.count(evidencijski_broj))
      throw std::logic_error("Film s tim evidencijskim brojem vec postoji");

    Film *novi = new Film(evidencijski_broj, dvd, std::move(naziv_filma),
                          std::move(zanr), godina_produkcije);
    try {
      mapa_filmova.insert({evidencijski_broj, novi});
    } catch (...) {
      delete novi;
      throw;
    }
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
      if (par.second->DajPokKodKogaJe() == it_korisnik->second) {
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
