// TP 2025/2026: Zadaća 4, Zadatak 1
#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <utility>

typedef std::pair<double, double> Tacka;
enum class Pozicija { GoreLijevo, GoreDesno, DoljeLijevo, DoljeDesno };
enum class Smjer { Nalijevo, Nadesno };

class Pravougaonik {
  Tacka gore_lijevo, dolje_desno;

  static constexpr double EPS = 1e-10;

  static bool Jednako(double x, double y) {
    return std::fabs(x - y) <= EPS * (1 + std::fabs(x) + std::fabs(y));
  }

  static bool ManjeIliJednako(double x, double y) {
    return x < y || Jednako(x, y);
  }

  static Tacka RotiranaTacka(const Tacka &p, const Tacka &centar, Smjer s) {
    double x = p.first, y = p.second;
    double a = centar.first, b = centar.second;

    if (s == Smjer::Nalijevo)
      return {a + b - y, b - a + x};

    return {a - b + y, a + b - x};
  }

public:
  Pravougaonik(const Tacka &t1, const Tacka &t2) { Postavi(t1, t2); }

  void Postavi(const Tacka &t1, const Tacka &t2) {
    gore_lijevo = {std::min(t1.first, t2.first),
                   std::max(t1.second, t2.second)};

    dolje_desno = {std::max(t1.first, t2.first),
                   std::min(t1.second, t2.second)};
  }

  void Postavi(Pozicija poz, const Tacka &t) {
    Tacka suprotno;

    if (poz == Pozicija::GoreLijevo)
      suprotno = DajTjeme(Pozicija::DoljeDesno);
    else if (poz == Pozicija::GoreDesno)
      suprotno = DajTjeme(Pozicija::DoljeLijevo);
    else if (poz == Pozicija::DoljeLijevo)
      suprotno = DajTjeme(Pozicija::GoreDesno);
    else
      suprotno = DajTjeme(Pozicija::GoreLijevo);

    Postavi(t, suprotno);
  }

  void Centriraj(const Tacka &t) {
    double h = DajHorizontalnu();
    double v = DajVertikalnu();

    gore_lijevo = {t.first - h / 2, t.second + v / 2};
    dolje_desno = {t.first + h / 2, t.second - v / 2};
  }

  Tacka DajTjeme(Pozicija poz) const {
    if (poz == Pozicija::GoreLijevo)
      return gore_lijevo;

    if (poz == Pozicija::GoreDesno)
      return {dolje_desno.first, gore_lijevo.second};

    if (poz == Pozicija::DoljeLijevo)
      return {gore_lijevo.first, dolje_desno.second};

    return dolje_desno;
  }

  Tacka DajCentar() const {
    return {(gore_lijevo.first + dolje_desno.first) / 2,
            (gore_lijevo.second + dolje_desno.second) / 2};
  }

  double DajHorizontalnu() const {
    return dolje_desno.first - gore_lijevo.first;
  }

  double DajVertikalnu() const {
    return gore_lijevo.second - dolje_desno.second;
  }

  double DajObim() const { return 2 * (DajHorizontalnu() + DajVertikalnu()); }

  double DajPovrsinu() const { return DajHorizontalnu() * DajVertikalnu(); }

  void Transliraj(double delta_x, double delta_y) {
    gore_lijevo.first += delta_x;
    gore_lijevo.second += delta_y;

    dolje_desno.first += delta_x;
    dolje_desno.second += delta_y;
  }

  void Rotiraj(const Tacka &t, Smjer s) {
    Tacka t1 = RotiranaTacka(gore_lijevo, t, s);
    Tacka t2 = RotiranaTacka(dolje_desno, t, s);

    Postavi(t1, t2);
  }

  void Ispisi() const {
    std::cout << "{{" << gore_lijevo.first << "," << gore_lijevo.second << "},{"
              << dolje_desno.first << "," << dolje_desno.second << "}}";
  }

  bool DaLiSadrzi(const Pravougaonik &p) const {
    return ManjeIliJednako(gore_lijevo.first, p.gore_lijevo.first) &&
           ManjeIliJednako(p.dolje_desno.first, dolje_desno.first) &&
           ManjeIliJednako(dolje_desno.second, p.dolje_desno.second) &&
           ManjeIliJednako(p.gore_lijevo.second, gore_lijevo.second);
  }

  bool DaLiSeSijeceSa(const Pravougaonik &p) const {
    double l1 = gore_lijevo.first;
    double r1 = dolje_desno.first;
    double b1 = dolje_desno.second;
    double t1 = gore_lijevo.second;

    double l2 = p.gore_lijevo.first;
    double r2 = p.dolje_desno.first;
    double b2 = p.dolje_desno.second;
    double t2 = p.gore_lijevo.second;

    bool imaju_zajednickih_tacaka =
        ManjeIliJednako(std::max(l1, l2), std::min(r1, r2)) &&
        ManjeIliJednako(std::max(b1, b2), std::min(t1, t2));

    if (!imaju_zajednickih_tacaka)
      return false;

    bool p_strogo_unutra_ovog = l1 < l2 && r2 < r1 && b1 < b2 && t2 < t1;

    bool ovaj_strogo_unutra_p = l2 < l1 && r1 < r2 && b2 < b1 && t1 < t2;

    return !(p_strogo_unutra_ovog || ovaj_strogo_unutra_p);
  }

  static Pravougaonik Presjek(const Pravougaonik &p1, const Pravougaonik &p2) {
    double lijevo = std::max(p1.gore_lijevo.first, p2.gore_lijevo.first);
    double desno = std::min(p1.dolje_desno.first, p2.dolje_desno.first);
    double gore = std::min(p1.gore_lijevo.second, p2.gore_lijevo.second);
    double dolje = std::max(p1.dolje_desno.second, p2.dolje_desno.second);

    if (!ManjeIliJednako(lijevo, desno) || !ManjeIliJednako(dolje, gore))
      throw std::domain_error("Pravougaonici se ne presjecaju");

    return Pravougaonik({lijevo, gore}, {desno, dolje});
  }

  friend bool DaLiSePoklapaju(const Pravougaonik &p1, const Pravougaonik &p2);
  friend bool DaLiSuPodudarni(const Pravougaonik &p1, const Pravougaonik &p2);
  friend bool DaLiSuSlicni(const Pravougaonik &p1, const Pravougaonik &p2);
};

bool DaLiSePoklapaju(const Pravougaonik &p1, const Pravougaonik &p2) {
  return Pravougaonik::Jednako(p1.gore_lijevo.first, p2.gore_lijevo.first) &&
         Pravougaonik::Jednako(p1.gore_lijevo.second, p2.gore_lijevo.second) &&
         Pravougaonik::Jednako(p1.dolje_desno.first, p2.dolje_desno.first) &&
         Pravougaonik::Jednako(p1.dolje_desno.second, p2.dolje_desno.second);
}

bool DaLiSuPodudarni(const Pravougaonik &p1, const Pravougaonik &p2) {
  double h1 = p1.DajHorizontalnu();
  double v1 = p1.DajVertikalnu();

  double h2 = p2.DajHorizontalnu();
  double v2 = p2.DajVertikalnu();

  return (Pravougaonik::Jednako(h1, h2) && Pravougaonik::Jednako(v1, v2)) ||
         (Pravougaonik::Jednako(h1, v2) && Pravougaonik::Jednako(v1, h2));
}

bool DaLiSuSlicni(const Pravougaonik &p1, const Pravougaonik &p2) {
  double a1 = std::max(p1.DajHorizontalnu(), p1.DajVertikalnu());
  double b1 = std::min(p1.DajHorizontalnu(), p1.DajVertikalnu());

  double a2 = std::max(p2.DajHorizontalnu(), p2.DajVertikalnu());
  double b2 = std::min(p2.DajHorizontalnu(), p2.DajVertikalnu());

  bool p1_tacka = Pravougaonik::Jednako(a1, 0) && Pravougaonik::Jednako(b1, 0);
  bool p2_tacka = Pravougaonik::Jednako(a2, 0) && Pravougaonik::Jednako(b2, 0);

  if (p1_tacka || p2_tacka)
    return true;

  bool p1_duz = Pravougaonik::Jednako(b1, 0);
  bool p2_duz = Pravougaonik::Jednako(b2, 0);

  if (p1_duz || p2_duz)
    return p1_duz && p2_duz;

  return Pravougaonik::Jednako(a1 * b2, a2 * b1);
}

int main() {
  int n;
  std::cout << "Unesite n: ";
  std::cin >> n;

  Pravougaonik **pravougaonici = nullptr;

  try {
    pravougaonici = new Pravougaonik *[n] {};

    for (int i = 0; i < n; i++) {
      double x1, y1, x2, y2;

      std::cout << "Unesite 1. tjeme pravougaonika " << i + 1 << ": ";
      std::cin >> x1 >> y1;

      std::cout << "Unesite 2. tjeme pravougaonika " << i + 1 << ": ";
      std::cin >> x2 >> y2;

      pravougaonici[i] = new Pravougaonik({x1, y1}, {x2, y2});
    }

    double delta_x, delta_y;
    std::cout << "Unesite podatke za transliranje (dx dy): ";
    std::cin >> delta_x >> delta_y;

    std::transform(pravougaonici, pravougaonici + n, pravougaonici,
                   [delta_x, delta_y](Pravougaonik *p) {
                     p->Transliraj(delta_x, delta_y);
                     return p;
                   });

    std::transform(pravougaonici, pravougaonici + n, pravougaonici,
                   [](Pravougaonik *p) {
                     p->Rotiraj(p->DajCentar(), Smjer::Nadesno);
                     return p;
                   });

    std::cout << "Pravougaonici, nakon transformacija:\n";

    std::for_each(pravougaonici, pravougaonici + n, [](Pravougaonik *p) {
      p->Ispisi();
      std::cout << "\n";
    });

    auto najveci =
        std::max_element(pravougaonici, pravougaonici + n,
                         [](Pravougaonik *p1, Pravougaonik *p2) {
                           return p1->DajPovrsinu() < p2->DajPovrsinu();
                         });

    if (n > 0) {
      std::cout << "Pravougaonik s najvecom povrsinom: ";
      (*najveci)->Ispisi();
      std::cout << "\n";
    }

    for (int i = 0; i < n; i++)
      delete pravougaonici[i];

    delete[] pravougaonici;
  } catch (...) {
    if (pravougaonici != nullptr) {
      for (int i = 0; i < n; i++)
        delete pravougaonici[i];

      delete[] pravougaonici;
    }

    throw;
  }

  return 0;
}