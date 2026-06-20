// TP 2025/2026: Zadaća 5, Zadatak 1
#include <cmath>
#include <complex>
#include <iostream>
#include <stdexcept>
#include <string_view>
#include <tuple>

class Sinusoida {
  double amplituda, frekvencija, faza;
  static constexpr double PI = 3.14159265358979323846;

  void Normaliziraj() {
    bool freq_negativna = (frekvencija < 0);
    bool amp_negativna = (amplituda < 0);

    if (freq_negativna)
      faza = -faza;
    if (freq_negativna != amp_negativna)
      faza += PI;

    frekvencija = std::abs(frekvencija);
    amplituda = std::abs(amplituda);

    faza = faza - 2 * PI * std::floor((faza + PI) / (2 * PI));
    if (std::abs(faza + PI) < 1e-10)
      faza = PI;
  }

public:
  Sinusoida(double amplituda, double frekvencija, double faza)
      : amplituda(amplituda), frekvencija(frekvencija), faza(faza) {
    Normaliziraj();
  }

  Sinusoida(const std::tuple<double, double, double> &parametri)
      : Sinusoida(std::get<0>(parametri), std::get<1>(parametri),
                  std::get<2>(parametri)) {}

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
    if (std::abs(s1.frekvencija - s2.frekvencija) > 1e-10)
      throw std::domain_error("Razlicite frekvencije");

    std::complex<double> fazor =
        std::polar(s1.amplituda, s1.faza) + std::polar(s2.amplituda, s2.faza);

    return Sinusoida(std::abs(fazor), s1.frekvencija, std::arg(fazor));
  }

  friend Sinusoida operator-(const Sinusoida &s1, const Sinusoida &s2) {
    if (std::abs(s1.frekvencija - s2.frekvencija) > 1e-10)
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

  std::cout << "Parametri s1: " << s1.DajAmplitudu() << ", "
            << s1.DajFrekvenciju() << ", " << s1.DajFazu() << '\n';

  auto parametri = s2.DajParametre();

  std::cout << "Parametri s2: " << std::get<0>(parametri) << ", "
            << std::get<1>(parametri) << ", " << std::get<2>(parametri) << '\n';

  std::cout << "Pristup pomocu []: " << s1["A"] << ", " << s1["omega"] << ", "
            << s1["phi"] << '\n';

  std::cout << "Vrijednost s1 za t = 1: " << s1(1) << '\n';

  Sinusoida zbir = s1 + s2;
  Sinusoida razlika = s1 - s2;

  std::cout << "Zbir: " << zbir["A"] << ", " << zbir["w"] << ", " << zbir["fi"]
            << '\n';

  std::cout << "Razlika: " << razlika["A"] << ", " << razlika["w"] << ", "
            << razlika["fi"] << '\n';

  Sinusoida negativna = -s2;
  Sinusoida proizvod1 = s2 * 3;
  Sinusoida proizvod2 = 3 * s2;
  Sinusoida kolicnik = s2 / 2;

  std::cout << "-s2: " << negativna["A"] << ", " << negativna["w"] << ", "
            << negativna["fi"] << '\n';

  std::cout << "s2 * 3: " << proizvod1["A"] << '\n';
  std::cout << "3 * s2: " << proizvod2["A"] << '\n';
  std::cout << "s2 / 2: " << kolicnik["A"] << '\n';

  Sinusoida s3(1, 3, 0);

  s3 += s2;
  s3 -= s2;
  s3 *= 4;
  s3 /= 2;

  std::cout << "Nakon slozenih operatora: " << s3["A"] << ", " << s3["w"]
            << ", " << s3["fi"] << '\n';

  s3.PostaviAmplitudu(-5).PostaviFrekvenciju(-2).PostaviFazu(15);

  std::cout << "Nakon pojedinacnih postavljanja: " << s3["A"] << ", " << s3["w"]
            << ", " << s3["fi"] << '\n';

  s3.PostaviParametre(-2, -3, 12);

  std::cout << "Nakon PostaviParametre sa tri parametra: " << s3["A"] << ", "
            << s3["w"] << ", " << s3["fi"] << '\n';

  s3.PostaviParametre(std::make_tuple(-1.0, -4.0, -15.0));

  std::cout << "Nakon PostaviParametre sa tuple: " << s3["A"] << ", " << s3["w"]
            << ", " << s3["fi"] << '\n';

  try {
    std::cout << s1["nepostojeci_parametar"] << '\n';
  } catch (const std::domain_error &e) {
    std::cout << e.what() << '\n';
  }

  try {
    Sinusoida s4(1, 100, 0);
    Sinusoida s5 = s1 + s4;
    std::cout << s5["A"] << '\n';
  } catch (const std::domain_error &e) {
    std::cout << e.what() << '\n';
  }

  return 0;
}
