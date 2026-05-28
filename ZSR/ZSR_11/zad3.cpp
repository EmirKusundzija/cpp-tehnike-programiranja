#include <algorithm>
#include <iostream>
#include <stdexcept>
// modernizacija
#include <vector>
class Temperature {
  int kapacitet;
  std::vector<double> temperature;

public:
  explicit Temperature(int V) : kapacitet(V) {
    if (V <= 0)
      throw std::domain_error("Prazna lista temperaturi");
    temperature.reserve(V);
  }
  double ProsjecnaTemperatura() const {
    if (temperature.empty())
      throw std::domain_error("Nema registrovanih temperatura");

    double suma = 0;
    for (int i = 0; i < temperature.size(); i++) {
      suma += temperature.at(i);
    }
    return suma / temperature.size();
  }
  void RegistrujTemperaturu(double t) {
    if (temperature.size() >= kapacitet)
      throw std::range_error("Dostignut maksimalan broj temperatura");
    temperature.push_back(t);
  }
  double MinTemperatura() const {
    if (temperature.empty()) {
      throw std::domain_error("Nema registrovanih temperatura, ne mozemo "
                              "odrediti minimalnu temperaturu");
    }

    return *std::min_element(temperature.begin(), temperature.end());
  }
  double MaxTemperatura() const {
    if (temperature.empty()) {
      throw std::domain_error("Nema registrovanih temperatura, ne mozemo "
                              "odrediti maksimalnu temperaturu");
    }
    return *std::max_element(temperature.begin(), temperature.end());
  }

  void Ispisi() const;
};

void Temperature::Ispisi() const {
  std::vector<double> temps(temperature);
  std::sort(temps.begin(), temps.end(),
            [](double temp1, double temp2) { return temp1 > temp2; });

  for (auto &x : temps) {
    std::cout << x << "\n";
  }
}

int main() {
  try {
    Temperature a(3);

    a.RegistrujTemperaturu(3);
    a.RegistrujTemperaturu(10);
    a.RegistrujTemperaturu(50);

    std::cout << "Ispis a:\n";
    a.Ispisi();

    std::cout << "Prosjek: " << a.ProsjecnaTemperatura() << "\n";
    std::cout << "Min: " << a.MinTemperatura() << "\n";
    std::cout << "Max: " << a.MaxTemperatura() << "\n";

    std::cout << "\nTest kopirajuceg konstruktora:\n";
    Temperature b(a);
    b.Ispisi();

    std::cout << "\nTest operatora dodjele:\n";
    Temperature c(5);
    c = a;
    c.Ispisi();

    std::cout << "\nTest samododjele:\n";
    a = a;
    a.Ispisi();

    std::cout << "\nTest prekoracenja kapaciteta:\n";
    a.RegistrujTemperaturu(100); // ovdje treba baciti izuzetak

  } catch (std::exception &e) {
    std::cout << "Izuzetak: " << e.what() << "\n";
  }

  try {
    std::cout << "\nTest prazne liste:\n";
    Temperature p(5);
    std::cout << p.ProsjecnaTemperatura() << "\n";
  } catch (std::exception &e) {
    std::cout << "Izuzetak: " << e.what() << "\n";
  }

  try {
    std::cout << "\nTest neispravnog konstruktora:\n";
    Temperature losa(0);
  } catch (std::exception &e) {
    std::cout << "Izuzetak: " << e.what() << "\n";
  }

  return 0;
}