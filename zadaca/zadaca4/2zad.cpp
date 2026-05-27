// TP 2025/2026: Zadaća 4, Zadatak 2
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>

class GradjaninBiH {
public:
  enum class Pol { Musko, Zensko, Bipolarno };

private:
  std::string ime_i_prezime;
  long long int jmbg;
  Pol pol;
  GradjaninBiH *prethodni;

  static GradjaninBiH *posljednji;

  static bool Prestupna(int godina) {
    return godina % 4 == 0 && godina % 100 != 0 || godina % 400 == 0;
  }

  static bool IspravanDatum(int dan, int mjesec, int godina) {
    int broj_dana[12]{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (godina < 1 || godina > 2026 || mjesec < 1 || mjesec > 12 || dan < 1)
      return false;

    if (Prestupna(godina))
      broj_dana[1]++;
    return dan <= broj_dana[mjesec - 1];
  }

  static void RastaviJMBG(long long int jmbg, int cifre[13]) {
    if (jmbg < 0)
      throw std::logic_error("JMBG nije validan");

    for (int i = 12; i >= 0; i--) {
      cifre[i] = jmbg % 10;
      jmbg /= 10;
    }

    if (jmbg != 0)
      throw std::logic_error("JMBG nije validan");
  }

  static int KontrolnaCifra(const int cifre[13]) {
    int suma = 7 * (cifre[0] + cifre[6]) + 6 * (cifre[1] + cifre[7]) +
               5 * (cifre[2] + cifre[8]) + 4 * (cifre[3] + cifre[9]) +
               3 * (cifre[4] + cifre[10]) + 2 * (cifre[5] + cifre[11]);

    int kontrolna = 11 - suma % 11;
    if (kontrolna == 11)
      kontrolna = 0;
    return kontrolna;
  }

  static int GodinaIzTriCifre(int godina) {
    if (godina <= 26)
      return 2000 + godina;
    return 1000 + godina;
  }

  static int DajDanIzJMBG(long long int jmbg) {
    int cifre[13];
    RastaviJMBG(jmbg, cifre);
    return 10 * cifre[0] + cifre[1];
  }

  static int DajMjesecIzJMBG(long long int jmbg) {
    int cifre[13];
    RastaviJMBG(jmbg, cifre);
    return 10 * cifre[2] + cifre[3];
  }

  static int DajGodinuIzJMBG(long long int jmbg) {
    int cifre[13];
    RastaviJMBG(jmbg, cifre);
    int godina = 100 * cifre[4] + 10 * cifre[5] + cifre[6];
    return GodinaIzTriCifre(godina);
  }

  static int DajSifruRegijeIzJMBG(long long int jmbg) {
    int cifre[13];
    RastaviJMBG(jmbg, cifre);
    return 10 * cifre[7] + cifre[8];
  }

  static int DajKodIzJMBG(long long int jmbg) {
    int cifre[13];
    RastaviJMBG(jmbg, cifre);
    return 100 * cifre[9] + 10 * cifre[10] + cifre[11];
  }

  static Pol DajPolIzJMBG(long long int jmbg) {
    if (DajKodIzJMBG(jmbg) < 500)
      return Pol::Musko;
    return Pol::Zensko;
  }

  static bool IspravanJMBG(long long int jmbg) {
    int cifre[13];
    RastaviJMBG(jmbg, cifre);

    int dan = 10 * cifre[0] + cifre[1];
    int mjesec = 10 * cifre[2] + cifre[3];
    int godina = GodinaIzTriCifre(100 * cifre[4] + 10 * cifre[5] + cifre[6]);

    if (!IspravanDatum(dan, mjesec, godina))
      return false;

    int kontrolna = KontrolnaCifra(cifre);
    return kontrolna != 10 && kontrolna == cifre[12];
  }

  static bool PostojiJMBG(long long int jmbg) {
    for (GradjaninBiH *p = posljednji; p != nullptr; p = p->prethodni)
      if (p->jmbg == jmbg)
        return true;
    return false;
  }

  static long long int SastaviJMBG(int dan, int mjesec, int godina,
                                   int sifra_regije, int kod) {

    int cifre[13]{};
    int godina_tri = godina % 1000;

    cifre[0] = dan / 10;
    cifre[1] = dan % 10;
    cifre[2] = mjesec / 10;
    cifre[3] = mjesec % 10;
    cifre[4] = godina_tri / 100;
    cifre[5] = (godina_tri / 10) % 10;
    cifre[6] = godina_tri % 10;
    cifre[7] = sifra_regije / 10;
    cifre[8] = sifra_regije % 10;
    cifre[9] = kod / 100;
    cifre[10] = (kod / 10) % 10;
    cifre[11] = kod % 10;

    int kontrolna = KontrolnaCifra(cifre);
    if (kontrolna == 10)
      return -1;
    cifre[12] = kontrolna;

    long long int rezultat = 0;
    for (int i = 0; i < 13; i++)
      rezultat = 10 * rezultat + cifre[i];
    return rezultat;
  }

  static bool KodOdgovaraPolu(int kod, Pol pol) {
    if (pol == Pol::Musko)
      return kod >= 0 && kod <= 499;
    if (pol == Pol::Zensko)
      return kod >= 500 && kod <= 999;
    return kod >= 0 && kod <= 999;
  }

  static long long int KreirajJMBG(int dan, int mjesec, int godina,
                                   int sifra_regije, Pol pol) {

    for (int kod = 0; kod <= 999; kod++) {
      if (!KodOdgovaraPolu(kod, pol))
        continue;

      long long int kandidat =
          SastaviJMBG(dan, mjesec, godina, sifra_regije, kod);
      if (kandidat != -1 && !PostojiJMBG(kandidat))
        return kandidat;
    }

    throw std::logic_error("Neispravni podaci");
  }

  void UveziUListu() {
    prethodni = posljednji;
    posljednji = this;
  }

public:
  GradjaninBiH(std::string_view ime_i_prezime, long long int jmbg);
  GradjaninBiH(std::string_view ime_i_prezime, int dan, int mjesec, int godina,
               int sifra_regije, Pol pol);
  ~GradjaninBiH();

  GradjaninBiH(const GradjaninBiH &g) = delete;
  GradjaninBiH &operator=(const GradjaninBiH &g) = delete;

  std::string DajImeIPrezime() const { return ime_i_prezime; }
  long long int DajJMBG() const { return jmbg; }
  int DajDanRodjenja() const { return DajDanIzJMBG(jmbg); }
  int DajMjesecRodjenja() const { return DajMjesecIzJMBG(jmbg); }
  int DajGodinuRodjenja() const { return DajGodinuIzJMBG(jmbg); }
  int DajSifruRegije() const { return DajSifruRegijeIzJMBG(jmbg); }
  Pol DajPol() const { return pol; }

  void PromijeniImeIPrezime(std::string_view novo_ime) {
    ime_i_prezime = std::string(novo_ime);
  }
};

GradjaninBiH *GradjaninBiH::posljednji = nullptr;

GradjaninBiH::GradjaninBiH(std::string_view ime_i_prezime, long long int jmbg)
    : ime_i_prezime(ime_i_prezime), jmbg(jmbg), pol(Pol::Musko),
      prethodni(nullptr) {

  if (!IspravanJMBG(jmbg))
    throw std::logic_error("JMBG nije validan");
  if (PostojiJMBG(jmbg))
    throw std::logic_error("Vec postoji gradjanin sa istim JMBG");

  pol = DajPolIzJMBG(jmbg);
  UveziUListu();
}

GradjaninBiH::GradjaninBiH(std::string_view ime_i_prezime, int dan, int mjesec,
                           int godina, int sifra_regije, Pol pol)
    : ime_i_prezime(ime_i_prezime), jmbg(0), pol(pol), prethodni(nullptr) {

  if (!IspravanDatum(dan, mjesec, godina) || sifra_regije < 0 ||
      sifra_regije > 99)
    throw std::logic_error("Neispravni podaci");

  jmbg = KreirajJMBG(dan, mjesec, godina, sifra_regije, pol);
  UveziUListu();
}

GradjaninBiH::~GradjaninBiH() {
  if (posljednji == this) {
    posljednji = prethodni;
    return;
  }

  for (GradjaninBiH *p = posljednji; p != nullptr; p = p->prethodni) {
    if (p->prethodni == this) {
      p->prethodni = prethodni;
      return;
    }
  }
}

int main() {
  try {
    GradjaninBiH g1("Rambo Sulejmanovic", 1305956174235);
    GradjaninBiH g2("Neko Drugi", 13, 5, 1956, 17, GradjaninBiH::Pol::Musko);

    std::cout << g1.DajImeIPrezime() << " " << g1.DajDanRodjenja() << "."
              << g1.DajMjesecRodjenja() << "." << g1.DajGodinuRodjenja() << " "
              << g1.DajJMBG() << std::endl;
    std::cout << g2.DajImeIPrezime() << " " << g2.DajJMBG() << std::endl;
  } catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
