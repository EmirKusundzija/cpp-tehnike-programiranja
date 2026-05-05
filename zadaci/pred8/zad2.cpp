// zadatak uz upotrebu pametnih pokazivaca
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

template <typename T> using PametniPok = std::shared_ptr<T>;

const int BrojPredmeta = 8;
struct Datum {
  int dan, mjesec, godina;
};
struct Ucenik {
  std::string ime, prezime;
  Datum datum_rodjenja;
  int ocjene[BrojPredmeta];
  double prosjek;
  bool prolaz;
};
int main() {
  void UnesiUcenike(std::vector<PametniPok<Ucenik>> & p_ucenici);
  void ObradiUcenike(std::vector<PametniPok<Ucenik>> & p_ucenici);
  void IspisiIzvjestaj(const std::vector<PametniPok<Ucenik>> &p_ucenici);
  int broj_ucenika;
  std::cout << "Koliko ima učenika: ";
  std::cin >> broj_ucenika;
  try {
    std::vector<PametniPok<Ucenik>> p_ucenici(broj_ucenika);
    UnesiUcenike(p_ucenici);
    ObradiUcenike(p_ucenici);
    IspisiIzvjestaj(p_ucenici);
  } catch (...) {
    std::cout << "Problemi s memorijom...\n";
  }
  return 0;
}

void UnesiUcenike(std::vector<PametniPok<Ucenik>> &p_ucenici) {
  void UnesiJednogUcenika(PametniPok<Ucenik> p_ucenik);
  for (int i = 0; i < p_ucenici.size(); i++) {
    std::cout << "Unesite podatke za " << i + 1 << ". učenika:\n";
    p_ucenici[i] = std::make_shared<Ucenik>();
    UnesiJednogUcenika(p_ucenici[i]);
  }
}
void UnesiJednogUcenika(PametniPok<Ucenik> p_ucenik) {
  void UnesiDatum(Datum & datum);
  void UnesiOcjene(int ocjene[], int broj_predmeta);
  std::cout << " Ime: ";
  std::cin >> p_ucenik->ime;
  std::cout << " Prezime: ";
  std::cin >> p_ucenik->prezime;
  std::cout << " Datum rođenja (D/M/G): ";
  UnesiDatum(p_ucenik->datum_rodjenja);
  UnesiOcjene(p_ucenik->ocjene, BrojPredmeta);
}
void UnesiDatum(Datum &datum) {
  char znak;
  std::cin >> datum.dan >> znak >> datum.mjesec >> znak >> datum.godina;
}
void UnesiOcjene(int ocjene[], int broj_predmeta) {
  void UnesiOcjenu(int &ocjena);
  for (int i = 0; i < broj_predmeta; i++) {
    std::cout << " Ocjena iz " << i + 1 << ". predmeta: ";
    UnesiOcjenu(ocjene[i]);
  }
}
void UnesiOcjenu(int &ocjena) { std::cin >> ocjena; }
void ObradiUcenike(std::vector<PametniPok<Ucenik>> &p_ucenici) {
  void ObradiJednogUcenika(PametniPok<Ucenik> p_ucenik);
  for (auto p_ucenik : p_ucenici)
    ObradiJednogUcenika(p_ucenik);
  std::sort(p_ucenici.begin(), p_ucenici.end(),
            [](const PametniPok<Ucenik> p_u1, const PametniPok<Ucenik> p_u2) {
              return p_u1->prosjek > p_u2->prosjek;
            });
}
void ObradiJednogUcenika(PametniPok<Ucenik> p_ucenik) {
  double suma_ocjena = 0;
  p_ucenik->prosjek = 1;
  p_ucenik->prolaz = false;
  for (int ocjena : p_ucenik->ocjene) {
    if (ocjena == 1)
      return;
    suma_ocjena += ocjena;
  }
  p_ucenik->prolaz = true;
  p_ucenik->prosjek = suma_ocjena / BrojPredmeta;
}
void IspisiIzvjestaj(const std::vector<PametniPok<Ucenik>> &p_ucenici) {
  void IspisiJednogUcenika(const PametniPok<Ucenik> p_ucenik);
  std::cout << std::endl;
  for (auto p_ucenik : p_ucenici)
    IspisiJednogUcenika(p_ucenik);
}
void IspisiJednogUcenika(const PametniPok<Ucenik> p_ucenik) {
  void IspisiDatum(const Datum &datum);
  std::cout << "Učenik " << p_ucenik->ime << " " << p_ucenik->prezime
            << " rodjen ";
  IspisiDatum(p_ucenik->datum_rodjenja);
  if (p_ucenik->prolaz)
    std::cout << " ima prosjek " << std::setprecision(3) << p_ucenik->prosjek;
  else
    std::cout << " mora ponavljati razred";
  std::cout << std::endl;
}
void IspisiDatum(const Datum &datum) {
  std::cout << datum.dan << "/" << datum.mjesec << "/" << datum.godina;
}
