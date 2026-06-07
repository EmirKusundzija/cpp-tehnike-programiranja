// TP 2025/2026: Zadaća 5, Zadatak 2
#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <stdexcept>

class Padavine {
  std::list<int> kolekcija_padavina;
  int max_kolicina;

public:
  explicit Padavine(int kolicina) : max_kolicina(kolicina) {
    if (kolicina <= 0)
      throw std::range_error("Ilegalna maksimalna kolicina");
  }

  void RegistrirajPadavine(int kolicina);
  int DajBrojRegistriranihPadavina() const { return kolekcija_padavina.size(); }
  void BrisiSve() { kolekcija_padavina.clear(); }
  int DajMinimalnuKolicinuPadavina() const;
  int DajMaksimalnuKolicinuPadavina() const;
  int DajBrojDanaSaPadavinamaVecimOd(int kolicina) const;
  int operator[](int indeks) const;
  Padavine &operator++();
  Padavine operator++(int);
  Padavine &operator+=(int broj);
  Padavine &operator-=(int broj);
  Padavine &operator-=(const Padavine &p);

  friend std::ostream &operator<<(std::ostream &tok, const Padavine &p);
  friend Padavine operator+(const Padavine &p, int broj);
  friend Padavine operator+(int broj, const Padavine &p);
  friend Padavine operator-(const Padavine &p, int broj);
  friend Padavine operator-(int broj, const Padavine &p);
  friend Padavine operator-(const Padavine &p1, const Padavine &p2);
  friend Padavine operator-(const Padavine &p);
  friend bool operator==(const Padavine &p1, const Padavine &p2);
  friend bool operator!=(const Padavine &p1, const Padavine &p2);
};

void Padavine::RegistrirajPadavine(int kolicina) {
  if (kolicina < 0 || kolicina > max_kolicina)
    throw std::range_error("Ilegalna kolicina padavina");

  kolekcija_padavina.push_back(kolicina);
}

int Padavine::DajMinimalnuKolicinuPadavina() const {
  if (kolekcija_padavina.empty())
    throw std::range_error("Nema registriranih padavina");

  return *std::min_element(kolekcija_padavina.begin(),
                           kolekcija_padavina.end());
}

int Padavine::DajMaksimalnuKolicinuPadavina() const {
  if (kolekcija_padavina.empty())
    throw std::range_error("Nema registriranih padavina");

  return *std::max_element(kolekcija_padavina.begin(),
                           kolekcija_padavina.end());
}

int Padavine::DajBrojDanaSaPadavinamaVecimOd(int kolicina) const {
  if (kolekcija_padavina.empty())
    throw std::range_error("Nema registriranih padavina");

  using std::placeholders::_1;
  return static_cast<int>(
      std::count_if(kolekcija_padavina.begin(), kolekcija_padavina.end(),
                    std::bind(std::greater<int>(), _1, kolicina)));
}

int Padavine::operator[](int indeks) const {
  if (indeks < 1 || indeks > DajBrojRegistriranihPadavina())
    throw std::range_error("Neispravan indeks");

  auto it = kolekcija_padavina.begin();
  std::advance(it, indeks - 1);
  return *it;
}

Padavine &Padavine::operator++() {
  using std::placeholders::_1;
  std::transform(kolekcija_padavina.begin(), kolekcija_padavina.end(),
                 kolekcija_padavina.begin(),
                 std::bind(std::plus<int>(), _1, 1));
  max_kolicina++;
  return *this;
}

Padavine Padavine::operator++(int) {
  Padavine kopija(*this);
  ++*this;
  return kopija;
}

Padavine operator+(const Padavine &p, int broj) {
  Padavine rezultat(p);
  using std::placeholders::_1;

  std::transform(rezultat.kolekcija_padavina.begin(),
                 rezultat.kolekcija_padavina.end(),
                 rezultat.kolekcija_padavina.begin(),
                 std::bind(std::plus<int>(), _1, broj));

  if (std::find_if(rezultat.kolekcija_padavina.begin(),
                   rezultat.kolekcija_padavina.end(),
                   std::bind(std::less<int>(), _1, 0)) !=
      rezultat.kolekcija_padavina.end())
    throw std::domain_error("Nekorektan rezultat operacije");

  rezultat.max_kolicina += broj;
  return rezultat;
}

Padavine operator+(int broj, const Padavine &p) { return p + broj; }

Padavine operator-(const Padavine &p, int broj) {
  Padavine rezultat(p);
  using std::placeholders::_1;

  std::transform(rezultat.kolekcija_padavina.begin(),
                 rezultat.kolekcija_padavina.end(),
                 rezultat.kolekcija_padavina.begin(),
                 std::bind(std::minus<int>(), _1, broj));

  if (std::find_if(rezultat.kolekcija_padavina.begin(),
                   rezultat.kolekcija_padavina.end(),
                   std::bind(std::less<int>(), _1, 0)) !=
      rezultat.kolekcija_padavina.end())
    throw std::domain_error("Nekorektan rezultat operacije");

  rezultat.max_kolicina -= broj;
  return rezultat;
}

Padavine operator-(int broj, const Padavine &p) {
  Padavine rezultat(p);
  using std::placeholders::_1;

  std::transform(rezultat.kolekcija_padavina.begin(),
                 rezultat.kolekcija_padavina.end(),
                 rezultat.kolekcija_padavina.begin(),
                 std::bind(std::minus<int>(), broj, _1));

  if (std::find_if(rezultat.kolekcija_padavina.begin(),
                   rezultat.kolekcija_padavina.end(),
                   std::bind(std::less<int>(), _1, 0)) !=
      rezultat.kolekcija_padavina.end())
    throw std::domain_error("Nekorektan rezultat operacije");

  rezultat.max_kolicina = broj;
  return rezultat;
}

Padavine operator-(const Padavine &p1, const Padavine &p2) {
  if (p1.kolekcija_padavina.size() != p2.kolekcija_padavina.size() ||
      !std::equal(p1.kolekcija_padavina.begin(), p1.kolekcija_padavina.end(),
                  p2.kolekcija_padavina.begin(), std::greater_equal<int>()))
    throw std::domain_error("Nesaglasni operandi");

  Padavine rezultat(p1);
  std::transform(p1.kolekcija_padavina.begin(), p1.kolekcija_padavina.end(),
                 p2.kolekcija_padavina.begin(),
                 rezultat.kolekcija_padavina.begin(), std::minus<int>());
  return rezultat;
}

Padavine &Padavine::operator+=(int broj) { return *this = *this + broj; }

Padavine &Padavine::operator-=(int broj) { return *this = *this - broj; }

Padavine &Padavine::operator-=(const Padavine &p) { return *this = *this - p; }

Padavine operator-(const Padavine &p) {
  Padavine rezultat(p);
  using std::placeholders::_1;

  std::transform(rezultat.kolekcija_padavina.begin(),
                 rezultat.kolekcija_padavina.end(),
                 rezultat.kolekcija_padavina.begin(),
                 std::bind(std::minus<int>(), rezultat.max_kolicina, _1));
  return rezultat;
}

bool operator==(const Padavine &p1, const Padavine &p2) {
  return p1.kolekcija_padavina.size() == p2.kolekcija_padavina.size() &&
         std::equal(p1.kolekcija_padavina.begin(), p1.kolekcija_padavina.end(),
                    p2.kolekcija_padavina.begin());
}

bool operator!=(const Padavine &p1, const Padavine &p2) { return !(p1 == p2); }

std::ostream &operator<<(std::ostream &tok, const Padavine &p) {
  std::list<int> kopija(p.kolekcija_padavina);
  kopija.sort(std::greater<int>());
  std::copy(kopija.begin(), kopija.end(),
            std::ostream_iterator<int>(tok, "\n"));
  return tok;
}

int main() {
  try {
    Padavine p(20);
    p.RegistrirajPadavine(5);
    p.RegistrirajPadavine(12);
    p.RegistrirajPadavine(0);
    p.RegistrirajPadavine(20);

    std::cout << "Pocetne padavine:\n" << p;
    std::cout << "Broj registriranih padavina: "
              << p.DajBrojRegistriranihPadavina() << '\n';
    std::cout << "Minimalna kolicina: " << p.DajMinimalnuKolicinuPadavina()
              << '\n';
    std::cout << "Maksimalna kolicina: " << p.DajMaksimalnuKolicinuPadavina()
              << '\n';
    std::cout << "Broj dana sa padavinama vecim od 6: "
              << p.DajBrojDanaSaPadavinamaVecimOd(6) << '\n';
    std::cout << "Druga registrirana kolicina: " << p[2] << "\n\n";

    std::cout << "Rezultat p++:\n" << p++;
    std::cout << "Objekat p nakon p++:\n" << p;
    std::cout << "Rezultat ++p:\n" << ++p;

    std::cout << "Rezultat p + 3:\n" << p + 3;
    std::cout << "Rezultat 3 + p:\n" << 3 + p;
    std::cout << "Rezultat p - 1:\n" << p - 1;
    std::cout << "Rezultat 30 - p:\n" << 30 - p;
    std::cout << "Rezultat -p:\n" << -p;

    Padavine q(25);
    q.RegistrirajPadavine(1);
    q.RegistrirajPadavine(4);
    q.RegistrirajPadavine(2);
    q.RegistrirajPadavine(20);

    std::cout << "Padavine q:\n" << q;
    std::cout << "Rezultat p - q:\n" << p - q;

    Padavine kopija(p);
    std::cout << std::boolalpha;
    std::cout << "p == kopija: " << (p == kopija) << '\n';
    kopija += 2;
    std::cout << "kopija nakon kopija += 2:\n" << kopija;
    std::cout << "p != kopija: " << (p != kopija) << '\n';
    kopija -= 2;
    std::cout << "kopija nakon kopija -= 2:\n" << kopija;
    kopija -= q;
    std::cout << "kopija nakon kopija -= q:\n" << kopija;

    try {
      std::cout << p[0] << '\n';
    } catch (const std::range_error &e) {
      std::cout << e.what() << '\n';
    }

    try {
      std::cout << p - 3;
    } catch (const std::domain_error &e) {
      std::cout << e.what() << '\n';
    }

    p.BrisiSve();
    std::cout << "Broj padavina nakon BrisiSve: "
              << p.DajBrojRegistriranihPadavina() << '\n';

    try {
      std::cout << p.DajMinimalnuKolicinuPadavina() << '\n';
    } catch (const std::range_error &e) {
      std::cout << e.what() << '\n';
    }

    try {
      Padavine neispravne(0);
      std::cout << neispravne;
    } catch (const std::range_error &e) {
      std::cout << e.what() << '\n';
    }
  } catch (const std::exception &e) {
    std::cout << e.what() << '\n';
  }

  return 0;
}
