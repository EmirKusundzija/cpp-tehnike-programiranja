// TP 2025/2026: Zadaća 3, Task 1
#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

// neki korisni aliasi
template <typename T> using Cvor = std::pair<T, T>;

template <typename T> using VektorUredjenihParova = std::vector<Cvor<T>>;

std::vector<double>
IzracunajTezinskeKoeficijente(const VektorUredjenihParova<double> &cvorovi,
                              int d) {
  int n = cvorovi.size();
  std::vector<double> w(n);
  for (int i = 0; i < n; i++) {
    double suma = 0;

    // granice sume
    int donja_granica = std::max(0, i - d);
    int gornja_granica = std::min(i, n - d - 1);

    for (int k = donja_granica; k <= gornja_granica; k++) {
      double proizvod = 1;
      for (int j = k; j <= k + d; j++) {
        if (j != i) {
          proizvod *= cvorovi.at(i).first - cvorovi.at(j).first;
        }
      }
      if (k % 2 == 0)
        suma += 1 / proizvod;
      else
        suma -= 1 / proizvod;
    }
    w.at(i) = suma;
  }

  return w;
}

// Prva varijanta: cvorovi interpolacije i red
std::function<double(double)>
BaricentricnaInterpolacija(VektorUredjenihParova<double> cvorovi, int d) {
  int n = cvorovi.size();

  if (d < 0 || d >= n)
    throw std::domain_error("Nedozvoljen red");

  std::sort(cvorovi.begin(), cvorovi.end(),
            [](const Cvor<double> &a, const Cvor<double> &b) {
              return a.first < b.first;
            });

  for (int i = 0; i < n - 1; i++) {
    if (cvorovi.at(i).first == cvorovi.at(i + 1).first)
      throw std::domain_error("Neispravni cvorovi");
  }

  std::vector<double> w = IzracunajTezinskeKoeficijente(cvorovi, d);

  return [cvorovi, w](double x) {
    double brojnik = 0;
    double nazivnik = 0;

    for (int i = 0; i < int(cvorovi.size()); i++) {
      double x_i = cvorovi.at(i).first;
      double y_i = cvorovi.at(i).second;

      if (x == x_i)
        return y_i;

      double clan = w.at(i) / (x - x_i);
      brojnik += clan * y_i;
      nazivnik += clan;
    }
    return brojnik / nazivnik;
  };
}

// Druga varijanta: aproksimiranje funkcije
template <typename Funkcija>
std::function<double(double)>
BaricentricnaInterpolacija(Funkcija f, double xmin, double xmax, double dx,
                           int d) {
  if (xmin > xmax || dx <= 0)
    throw std::domain_error("Nekorektni parametri");

  VektorUredjenihParova<double> cvorovi;

  for (double x = xmin; x <= xmax; x += dx)
    cvorovi.push_back({x, f(x)});

  return BaricentricnaInterpolacija(cvorovi, d);
}

int main() {
  int opcija;
  std::cout << "Odaberite opciju (1 - unos cvorova, 2 - aproksimacija): ";
  std::cin >> opcija;

  try {
    switch (opcija) {
    case 1: {
      int n;
      std::cout << "Unesite broj cvorova: ";
      std::cin >> n;
      VektorUredjenihParova<double> parovi(n);
      std::cout << "Unesite cvorove kao parove x y: ";
      for (auto &cvor : parovi) {
        std::cin >> cvor.first >> cvor.second;
      }
      int d;
      std::cout << "Unesite red interpolacije: ";
      std::cin >> d;

      auto f1 = BaricentricnaInterpolacija(parovi, d);

      for (;;) {
        double x;
        std::cout << "Unesite argument (ili \"kraj\" za kraj): ";
        if (!(std::cin >> x))
          break;

        std::cout << "f(" << x << ") = " << f1(x) << "\n";
      }
      break;
    }
    case 2: {
      double pocetak, kraj, korak;
      auto f2 = [](double x) { return x * x + std::sin(x); };
      std::cout << "Unesite krajeve intervala i korak: ";
      std::cin >> pocetak >> kraj >> korak;
      int d;
      std::cout << "Unesite red interpolacije: ";
      std::cin >> d;

      auto fapprox = BaricentricnaInterpolacija(f2, pocetak, kraj, korak, d);
      for (;;) {
        double x;
        std::cout << "Unesite argument (ili \"kraj\" za kraj): ";
        if (!(std::cin >> x))
          break;

        std::cout << "f(" << x << ") = " << f2(x) << " fapprox(" << x
                  << ") = " << fapprox(x) << "\n";
      }

      break;
    }
    }
  } catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
