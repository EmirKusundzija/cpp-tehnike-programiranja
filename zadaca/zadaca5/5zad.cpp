// TP 2025/2026: Zadaća 5, Zadatak 5
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

template <typename TipEl> class Matrica {
  int br_redova, br_kolona;
  TipEl **elementi;
  char ime_matrice;

  static TipEl **AlocirajMemoriju(int br_redova, int br_kolona);
  static void DealocirajMemoriju(TipEl **elementi, int br_redova);
  void KopirajElemente(TipEl **elementi);
  static int DajBrojElemenataURedu(const std::string &red);

public:
  Matrica(int br_redova, int br_kolona, char ime = 0);
  Matrica(const Matrica &m);
  Matrica(Matrica &&m) noexcept;
  ~Matrica() { DealocirajMemoriju(elementi, br_redova); }
  Matrica &operator=(const Matrica &m);
  Matrica &operator=(Matrica &&m) noexcept;

  Matrica(const std::string &ime_datoteke, bool binarna);

  void SacuvajUTekstualnuDatoteku(const std::string &ime_datoteke) const;
  void SacuvajUBinarnuDatoteku(const std::string &ime_datoteke) const;
  void ObnoviIzTekstualneDatoteke(const std::string &ime_datoteke);
  void ObnoviIzBinarneDatoteke(const std::string &ime_datoteke);

  template <typename Tip2>
  friend std::istream &operator>>(std::istream &tok, Matrica<Tip2> &m);
  template <typename Tip2>
  friend std::ostream &operator<<(std::ostream &tok, const Matrica<Tip2> &m);
  template <typename Tip2>
  friend Matrica<Tip2> operator+(const Matrica<Tip2> &m1,
                                 const Matrica<Tip2> &m2);
  template <typename Tip2>
  friend Matrica<Tip2> operator-(const Matrica<Tip2> &m1,
                                 const Matrica<Tip2> &m2);
  template <typename Tip2>
  friend Matrica<Tip2> operator*(const Matrica<Tip2> &m1,
                                 const Matrica<Tip2> &m2);
  template <typename Tip2>
  friend Matrica<Tip2> operator*(const Matrica<Tip2> &m, Tip2 d);
  template <typename Tip2>
  friend Matrica<Tip2> operator*(Tip2 d, const Matrica<Tip2> &m);

  Matrica &operator+=(const Matrica &m);
  Matrica &operator-=(const Matrica &m);
  Matrica &operator*=(const Matrica &m);
  Matrica &operator*=(TipEl d);

  TipEl *operator[](int i) { return elementi[i]; }
  const TipEl *operator[](int i) const { return elementi[i]; }
  TipEl &operator()(int i, int j);
  const TipEl &operator()(int i, int j) const;

  operator std::string() const;
};

template <typename TipEl>
TipEl **Matrica<TipEl>::AlocirajMemoriju(int br_redova, int br_kolona) {
  TipEl **elementi = new TipEl *[br_redova] {};
  try {
    for (int i = 0; i < br_redova; i++)
      elementi[i] = new TipEl[br_kolona];
  } catch (...) {
    DealocirajMemoriju(elementi, br_redova);
    throw;
  }
  return elementi;
}

template <typename TipEl>
void Matrica<TipEl>::DealocirajMemoriju(TipEl **elementi, int br_redova) {
  for (int i = 0; i < br_redova; i++)
    delete[] elementi[i];
  delete[] elementi;
}

template <typename TipEl>
Matrica<TipEl>::Matrica(int br_redova, int br_kolona, char ime)
    : br_redova(br_redova), br_kolona(br_kolona),
      elementi(AlocirajMemoriju(br_redova, br_kolona)), ime_matrice(ime) {}

template <typename TipEl>
void Matrica<TipEl>::KopirajElemente(TipEl **elementi) {
  for (int i = 0; i < br_redova; i++)
    for (int j = 0; j < br_kolona; j++)
      Matrica::elementi[i][j] = elementi[i][j];
}

template <typename TipEl>
Matrica<TipEl>::Matrica(const Matrica &m)
    : br_redova(m.br_redova), br_kolona(m.br_kolona),
      elementi(AlocirajMemoriju(m.br_redova, m.br_kolona)),
      ime_matrice(m.ime_matrice) {
  KopirajElemente(m.elementi);
}

template <typename TipEl>
Matrica<TipEl>::Matrica(Matrica &&m) noexcept
    : br_redova(m.br_redova), br_kolona(m.br_kolona), elementi(m.elementi),
      ime_matrice(m.ime_matrice) {
  m.br_redova = 0;
  m.br_kolona = 0;
  m.elementi = nullptr;
}

template <typename TipEl>
Matrica<TipEl> &Matrica<TipEl>::operator=(const Matrica &m) {
  if (this != &m) {
    Matrica kopija(m);
    std::swap(br_redova, kopija.br_redova);
    std::swap(br_kolona, kopija.br_kolona);
    std::swap(elementi, kopija.elementi);
    std::swap(ime_matrice, kopija.ime_matrice);
  }
  return *this;
}

template <typename TipEl>
Matrica<TipEl> &Matrica<TipEl>::operator=(Matrica &&m) noexcept {
  if (this != &m) {
    std::swap(br_redova, m.br_redova);
    std::swap(br_kolona, m.br_kolona);
    std::swap(elementi, m.elementi);
    std::swap(ime_matrice, m.ime_matrice);
  }
  return *this;
}

template <typename TipEl>
int Matrica<TipEl>::DajBrojElemenataURedu(const std::string &red) {
  if (red.empty())
    throw std::logic_error("Datoteka sadrzi besmislene podatke");

  std::istringstream tok(red);
  int broj_elemenata = 0;

  for (;;) {
    TipEl element;
    if (!(tok >> element))
      throw std::logic_error("Datoteka sadrzi besmislene podatke");

    broj_elemenata++;
    tok >> std::ws;

    if (tok.eof())
      break;

    char znak;
    tok.get(znak);
    if (znak != ',')
      throw std::logic_error("Datoteka sadrzi besmislene podatke");

    tok >> std::ws;
    if (tok.eof())
      throw std::logic_error("Datoteka sadrzi besmislene podatke");
  }

  return broj_elemenata;
}

template <typename TipEl>
Matrica<TipEl>::Matrica(const std::string &ime_datoteke, bool binarna)
    : br_redova(0), br_kolona(0), elementi(nullptr), ime_matrice(0) {
  if (binarna)
    ObnoviIzBinarneDatoteke(ime_datoteke);
  else
    ObnoviIzTekstualneDatoteke(ime_datoteke);
}

template <typename TipEl>
void Matrica<TipEl>::SacuvajUTekstualnuDatoteku(
    const std::string &ime_datoteke) const {
  std::ofstream datoteka(ime_datoteke);
  if (!datoteka)
    throw std::logic_error("Problemi sa upisom u datoteku");

  for (int i = 0; i < br_redova; i++) {
    for (int j = 0; j < br_kolona; j++) {
      datoteka << elementi[i][j];
      if (j != br_kolona - 1)
        datoteka << ',';
    }
    if (i != br_redova - 1)
      datoteka << '\n';
  }

  if (!datoteka)
    throw std::logic_error("Problemi sa upisom u datoteku");
}

template <typename TipEl>
void Matrica<TipEl>::SacuvajUBinarnuDatoteku(
    const std::string &ime_datoteke) const {
  std::ofstream datoteka(ime_datoteke, std::ios::binary);
  if (!datoteka)
    throw std::logic_error("Problemi sa upisom u datoteku");

  datoteka.write(reinterpret_cast<const char *>(&br_redova), sizeof br_redova);
  datoteka.write(reinterpret_cast<const char *>(&br_kolona), sizeof br_kolona);

  for (int i = 0; i < br_redova; i++)
    datoteka.write(reinterpret_cast<const char *>(elementi[i]),
                   br_kolona * sizeof(TipEl));

  if (!datoteka)
    throw std::logic_error("Problemi sa upisom u datoteku");
}

template <typename TipEl>
void Matrica<TipEl>::ObnoviIzTekstualneDatoteke(
    const std::string &ime_datoteke) {
  std::ifstream datoteka(ime_datoteke);
  if (!datoteka)
    throw std::logic_error("Trazena datoteka ne postoji");

  int novi_br_redova = 0;
  int novi_br_kolona = -1;
  std::string red;

  while (std::getline(datoteka, red)) {
    int broj_elemenata = DajBrojElemenataURedu(red);

    if (novi_br_kolona == -1)
      novi_br_kolona = broj_elemenata;
    else if (novi_br_kolona != broj_elemenata)
      throw std::logic_error("Datoteka sadrzi besmislene podatke");

    novi_br_redova++;
  }

  if (datoteka.bad())
    throw std::logic_error("Problemi pri citanju datoteke");

  if (novi_br_redova == 0 || novi_br_kolona <= 0)
    throw std::logic_error("Datoteka sadrzi besmislene podatke");

  datoteka.clear();
  datoteka.seekg(0, std::ios::beg);
  if (!datoteka)
    throw std::logic_error("Problemi pri citanju datoteke");

  Matrica nova_matrica(novi_br_redova, novi_br_kolona, ime_matrice);

  for (int i = 0; i < novi_br_redova; i++) {
    if (!std::getline(datoteka, red))
      throw std::logic_error("Problemi pri citanju datoteke");

    std::istringstream tok(red);
    for (int j = 0; j < novi_br_kolona; j++) {
      if (!(tok >> nova_matrica.elementi[i][j]))
        throw std::logic_error("Datoteka sadrzi besmislene podatke");

      tok >> std::ws;
      if (j != novi_br_kolona - 1) {
        char znak;
        if (!tok.get(znak) || znak != ',')
          throw std::logic_error("Datoteka sadrzi besmislene podatke");
      } else if (!tok.eof()) {
        throw std::logic_error("Datoteka sadrzi besmislene podatke");
      }
    }
  }

  if (datoteka.bad())
    throw std::logic_error("Problemi pri citanju datoteke");

  *this = std::move(nova_matrica);
}

template <typename TipEl>
void Matrica<TipEl>::ObnoviIzBinarneDatoteke(
    const std::string &ime_datoteke) {
  std::ifstream datoteka(ime_datoteke, std::ios::binary);
  if (!datoteka)
    throw std::logic_error("Trazena datoteka ne postoji");

  datoteka.seekg(0, std::ios::end);
  std::streamoff duzina_datoteke = datoteka.tellg();
  datoteka.seekg(0, std::ios::beg);

  if (!datoteka || duzina_datoteke < static_cast<std::streamoff>(2 * sizeof(int)))
    throw std::logic_error("Problemi pri citanju datoteke");

  int novi_br_redova, novi_br_kolona;
  datoteka.read(reinterpret_cast<char *>(&novi_br_redova),
                sizeof novi_br_redova);
  datoteka.read(reinterpret_cast<char *>(&novi_br_kolona),
                sizeof novi_br_kolona);

  if (!datoteka || novi_br_redova < 0 || novi_br_kolona < 0)
    throw std::logic_error("Problemi pri citanju datoteke");

  std::streamoff velicina_podataka =
      duzina_datoteke - static_cast<std::streamoff>(2 * sizeof(int));
  std::streamoff broj_elemenata =
      static_cast<std::streamoff>(novi_br_redova) * novi_br_kolona;

  if (velicina_podataka % static_cast<std::streamoff>(sizeof(TipEl)) != 0 ||
      velicina_podataka / static_cast<std::streamoff>(sizeof(TipEl)) !=
          broj_elemenata)
    throw std::logic_error("Problemi pri citanju datoteke");

  Matrica nova_matrica(novi_br_redova, novi_br_kolona, ime_matrice);

  for (int i = 0; i < novi_br_redova; i++)
    datoteka.read(reinterpret_cast<char *>(nova_matrica.elementi[i]),
                  novi_br_kolona * sizeof(TipEl));

  if (!datoteka)
    throw std::logic_error("Problemi pri citanju datoteke");

  *this = std::move(nova_matrica);
}

template <typename TipEl> TipEl &Matrica<TipEl>::operator()(int i, int j) {
  if (i < 1 || i > br_redova || j < 1 || j > br_kolona)
    throw std::range_error("Neispravan indeks");
  return elementi[i - 1][j - 1];
}

template <typename TipEl>
const TipEl &Matrica<TipEl>::operator()(int i, int j) const {
  if (i < 1 || i > br_redova || j < 1 || j > br_kolona)
    throw std::range_error("Neispravan indeks");
  return elementi[i - 1][j - 1];
}

template <typename TipEl>
std::istream &operator>>(std::istream &tok, Matrica<TipEl> &m) {
  for (int i = 0; i < m.br_redova; i++)
    for (int j = 0; j < m.br_kolona; j++) {
      if (&tok == &std::cin)
        std::cout << m.ime_matrice << "(" << i + 1 << "," << j + 1 << ") = ";
      tok >> m.elementi[i][j];
    }
  return tok;
}

template <typename TipEl>
std::ostream &operator<<(std::ostream &tok, const Matrica<TipEl> &m) {
  int sirina_ispisa = static_cast<int>(tok.width());
  for (int i = 0; i < m.br_redova; i++) {
    for (int j = 0; j < m.br_kolona; j++)
      tok << std::setw(sirina_ispisa) << m.elementi[i][j];
    tok << '\n';
  }
  return tok;
}

template <typename TipEl>
Matrica<TipEl> operator+(const Matrica<TipEl> &m1, const Matrica<TipEl> &m2) {
  if (m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)
    throw std::domain_error("Matrice nemaju jednake dimenzije!");

  Matrica<TipEl> m3(m1.br_redova, m1.br_kolona);
  for (int i = 0; i < m1.br_redova; i++)
    for (int j = 0; j < m1.br_kolona; j++)
      m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
  return m3;
}

template <typename TipEl>
Matrica<TipEl> operator-(const Matrica<TipEl> &m1, const Matrica<TipEl> &m2) {
  if (m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)
    throw std::domain_error("Matrice nemaju jednake dimenzije!");

  Matrica<TipEl> m3(m1.br_redova, m1.br_kolona);
  for (int i = 0; i < m1.br_redova; i++)
    for (int j = 0; j < m1.br_kolona; j++)
      m3.elementi[i][j] = m1.elementi[i][j] - m2.elementi[i][j];
  return m3;
}

template <typename TipEl>
Matrica<TipEl> operator*(const Matrica<TipEl> &m1, const Matrica<TipEl> &m2) {
  if (m1.br_kolona != m2.br_redova)
    throw std::domain_error("Matrice nisu saglasne za mnozenje");

  Matrica<TipEl> m3(m1.br_redova, m2.br_kolona);
  for (int i = 0; i < m1.br_redova; i++)
    for (int j = 0; j < m2.br_kolona; j++) {
      m3.elementi[i][j] = TipEl();
      for (int k = 0; k < m1.br_kolona; k++)
        m3.elementi[i][j] += m1.elementi[i][k] * m2.elementi[k][j];
    }
  return m3;
}

template <typename TipEl>
Matrica<TipEl> operator*(const Matrica<TipEl> &m, TipEl d) {
  Matrica<TipEl> rezultat(m.br_redova, m.br_kolona);
  for (int i = 0; i < m.br_redova; i++)
    for (int j = 0; j < m.br_kolona; j++)
      rezultat.elementi[i][j] = m.elementi[i][j] * d;
  return rezultat;
}

template <typename TipEl>
Matrica<TipEl> operator*(TipEl d, const Matrica<TipEl> &m) {
  return m * d;
}

template <typename TipEl>
Matrica<TipEl> &Matrica<TipEl>::operator+=(const Matrica &m) {
  if (br_redova != m.br_redova || br_kolona != m.br_kolona)
    throw std::domain_error("Matrice nemaju jednake dimenzije!");

  for (int i = 0; i < br_redova; i++)
    for (int j = 0; j < br_kolona; j++)
      elementi[i][j] += m.elementi[i][j];
  return *this;
}

template <typename TipEl>
Matrica<TipEl> &Matrica<TipEl>::operator-=(const Matrica &m) {
  if (br_redova != m.br_redova || br_kolona != m.br_kolona)
    throw std::domain_error("Matrice nemaju jednake dimenzije!");

  for (int i = 0; i < br_redova; i++)
    for (int j = 0; j < br_kolona; j++)
      elementi[i][j] -= m.elementi[i][j];
  return *this;
}

template <typename TipEl>
Matrica<TipEl> &Matrica<TipEl>::operator*=(const Matrica &m) {
  return *this = *this * m;
}

template <typename TipEl> Matrica<TipEl> &Matrica<TipEl>::operator*=(TipEl d) {
  for (int i = 0; i < br_redova; i++)
    for (int j = 0; j < br_kolona; j++)
      elementi[i][j] *= d;
  return *this;
}

template <typename TipEl> Matrica<TipEl>::operator std::string() const {
  using std::to_string;
  std::string s = "{";
  for (int i = 0; i < br_redova; i++) {
    s += "{";
    for (int j = 0; j < br_kolona; j++) {
      s += to_string(elementi[i][j]);
      if (j != br_kolona - 1)
        s += ",";
    }
    s += "}";
    if (i != br_redova - 1)
      s += ",";
  }
  return s += "}";
}

int main() {
  try {
    Matrica<double> m(2, 3, 'A');
    m(1, 1) = 1.5;
    m(1, 2) = -2;
    m(1, 3) = 3.25;
    m(2, 1) = 4;
    m(2, 2) = 5.5;
    m(2, 3) = 6;

    std::cout << "Pocetna matrica:\n" << std::setw(8) << m;

    m.SacuvajUTekstualnuDatoteku("MATRICA.TXT");
    std::cout << "Matrica je sacuvana u tekstualnu datoteku.\n";

    m.SacuvajUBinarnuDatoteku("MATRICA.DAT");
    std::cout << "Matrica je sacuvana u binarnu datoteku.\n";

    Matrica<double> iz_tekstualne("MATRICA.TXT", false);
    std::cout << "Matrica obnovljena konstruktorom iz tekstualne datoteke:\n"
              << std::setw(8) << iz_tekstualne;

    Matrica<double> iz_binarne("MATRICA.DAT", true);
    std::cout << "Matrica obnovljena konstruktorom iz binarne datoteke:\n"
              << std::setw(8) << iz_binarne;

    m(1, 1) = 100;
    m.ObnoviIzTekstualneDatoteke("MATRICA.TXT");
    std::cout << "Postojeca matrica obnovljena iz tekstualne datoteke:\n"
              << std::setw(8) << m;

    m(1, 1) = 200;
    m.ObnoviIzBinarneDatoteke("MATRICA.DAT");
    std::cout << "Postojeca matrica obnovljena iz binarne datoteke:\n"
              << std::setw(8) << m;

    try {
      Matrica<double> nepostojeca("NEPOSTOJECA.TXT", false);
      std::cout << nepostojeca;
    } catch (const std::logic_error &e) {
      std::cout << e.what() << '\n';
    }

    {
      std::ofstream losa_datoteka("LOSA_MATRICA.TXT");
      losa_datoteka << "1,2,3\n4,5";
    }

    try {
      m.ObnoviIzTekstualneDatoteke("LOSA_MATRICA.TXT");
    } catch (const std::logic_error &e) {
      std::cout << e.what() << '\n';
    }
  } catch (const std::exception &e) {
    std::cout << e.what() << '\n';
  }

  return 0;
}
