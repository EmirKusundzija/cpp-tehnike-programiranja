// TP 2025/2026: Zadaća 5, Zadatak 1
#include <cmath>
#include <complex>
#include <iostream>
#include <tuple>
class Sinusoida {
  double amplituda, frekvencija, faza; // sve u radijanima
  static constexpr double PI = 3.14159265358979323846;
  void Normaliziraj() {
    if (amplituda < 0) {
      amplituda = -amplituda;
      faza += PI;
    }
    if (frekvencija < 0) {
      frekvencija = -frekvencija;
      faza = PI - faza;
    }
    faza = std::fmod(faza, 2 * PI);

    if (faza > PI)
      faza -= 2 * PI;
    if (faza < -PI)
      faza += 2 * PI;
  }

public:
  Sinusoida(double amplituda, double frekvencija, double faza)
      : amplituda(amplituda), frekvencija(frekvencija), faza(faza) {
    Normaliziraj();
  }
  Sinusoida(const std::tuple<double, double, double> &a)
      : Sinusoida(std::get<0>(a), std::get<1>(a), std::get<2>(a)) {}

  double DajAmplitudu() const { return amplituda; }
  double DajFrekvenciju() const { return frekvencija; }
  double DajFazu() const { return faza; }

  std::tuple<double, double, double> DajParametre() const {
    return std::make_tuple(amplituda, frekvencija, faza);
  }

  Sinusoida &PostaviAmplitudu(double amplituda) {
    this->amplituda = amplituda;
    Normaliziraj();
    return *this;
  }

  Sinusoida &PostaviFrekvenciju(double frekvencija) {
    this->frekvencija = frekvencija;
    Normaliziraj();
    return *this;
  }

  Sinusoida &PostaviFazu(double faza) {
    this->faza = faza;
    Normaliziraj();
    return *this;
  }

  Sinusoida &PostaviParametre(double amplituda, double frekvencija,
                              double faza) {
    this->amplituda = amplituda;
    this->frekvencija = frekvencija;
    this->faza = faza;

    Normaliziraj();
    return *this;
  }

  Sinusoida &
  PostaviParametre(const std::tuple<double, double, double> &parametri) {
    return PostaviParametre(std::get<0>(parametri), std::get<1>(parametri),
                            std::get<2>(parametri));
  }

  friend Sinusoida operator+(const Sinusoida &s1, const Sinusoida &s2) {
    if (s1.frekvencija != s2.frekvencija)
      throw std::domain_error("Razlicite frekvencije");

    std::complex<double> fazor =
        std::polar(s1.amplituda, s1.faza) + std::polar(s2.amplituda, s2.faza);

    return Sinusoida(std::abs(fazor), s1.frekvencija, std::arg(fazor));
  }

  friend Sinusoida operator-(const Sinusoida &s1, const Sinusoida &s2) {
    if (s1.frekvencija != s2.frekvencija)
      throw std::domain_error("Razlicite frekvencije");

    std::complex<double> fazor =
        std::polar(s1.amplituda, s1.faza) - std::polar(s2.amplituda, s2.faza);

    return Sinusoida(std::abs(fazor), s1.frekvencija, std::arg(fazor));
  }

  Sinusoida operator-() const {
    return Sinusoida(-amplituda, frekvencija, faza);
  }

  friend Sinusoida operator*(const Sinusoida &s, double broj) {
    return Sinusoida(s.amplituda * broj, s.frekvencija, s.faza);
  }

  friend Sinusoida operator*(double broj, const Sinusoida &s) {
    return s * broj;
  }

  friend Sinusoida operator/(const Sinusoida &s, double broj) {
    return Sinusoida(s.amplituda / broj, s.frekvencija, s.faza);
  }

  Sinusoida &operator+=(const Sinusoida &s) { return *this = *this + s; }

  Sinusoida &operator-=(const Sinusoida &s) { return *this = *this - s; }

  Sinusoida &operator*=(double broj) { return *this = *this * broj; }

  Sinusoida &operator/=(double broj) { return *this = *this / broj; }

  double operator[](std::string_view naziv_parametra) const {
    if (naziv_parametra == "A")
      return amplituda;

    if (naziv_parametra == "omega" || naziv_parametra == "w")
      return frekvencija;

    if (naziv_parametra == "phi" || naziv_parametra == "fi")
      return faza;

    throw std::domain_error("Neispravan naziv parametra");
  }

  double operator()(double t) const {
    return amplituda * std::sin(frekvencija * t + faza);
  }
};

int main() {
  Sinusoida s1(-2, 3, 0);
  Sinusoida s2(std::make_tuple(4.0, 3.0, 1.0));

  std::cout << "s1: " << s1["A"] << ", " << s1["omega"] << ", " << s1["phi"]
            << "\n";

  std::cout << "Vrijednost s1 za t = 1: " << s1(1) << "\n";

  Sinusoida zbir = s1 + s2;
  Sinusoida razlika = s1 - s2;

  std::cout << "Amplituda zbira: " << zbir.DajAmplitudu() << "\n";
  std::cout << "Amplituda razlike: " << razlika.DajAmplitudu() << "\n";

  s1.PostaviAmplitudu(-5).PostaviFrekvenciju(-2).PostaviFazu(15);

  std::cout << "Normalizirani parametri s1: " << s1["A"] << ", " << s1["w"]
            << ", " << s1["fi"] << "\n";

  Sinusoida s3 = -s2;
  Sinusoida s4 = 3 * s2;
  Sinusoida s5 = s2 / 2;

  s3 += s2;
  s4 -= s2;
  s5 *= 4;
  s5 /= 2;

  try {
    std::cout << s1["nepostojeci_parametar"];
  } catch (const std::domain_error &e) {
    std::cout << e.what() << "\n";
  }

  try {
    Sinusoida s6(1, 100, 0);
    Sinusoida s7 = s1 + s6;
  } catch (const std::domain_error &e) {
    std::cout << e.what() << "\n";
  }
}
