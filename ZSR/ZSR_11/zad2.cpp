#include <algorithm>
#include <iostream>
#include <stdexcept>

class Temperature {
  int velicina; // veze za velicinu niza tipa "Temperature"
  int broj_temperatura;
  double *temperature;

public:
  explicit Temperature(int V)
      : velicina(V), broj_temperatura(0), temperature(nullptr) {
    if (V <= 0)
      throw std::domain_error("Prazna lista temperaturi");

    temperature = new double[V];
  }
  ~Temperature() { delete[] temperature; }
  Temperature(const Temperature &t);

  Temperature &operator=(const Temperature &t);
  void BrisiTemperature() { broj_temperatura = 0; }
  void RegistrujTemperaturu(double t) {
    if (broj_temperatura >= velicina)
      throw std::range_error("Dostignut maksimalan broj temperatura");
    temperature[broj_temperatura] = t;
    broj_temperatura++;
  }
  double ProsjecnaTemperatura() const {
    if (broj_temperatura == 0)
      throw std::domain_error("Nema registrovanih temperatura");

    double suma = 0;
    for (int i = 0; i < broj_temperatura; i++) {
      suma += temperature[i];
    }
    return suma / broj_temperatura;
  }
  double MinTemperatura() const {
    if (broj_temperatura == 0) {
      throw std::domain_error("Nema registrovanih temperatura, ne mozemo "
                              "odrediti minimalnu temperaturu");
    }

    return *std::min_element(temperature, temperature + broj_temperatura);
  }
  double MaxTemperatura() const {
    if (broj_temperatura == 0) {
      throw std::domain_error("Nema registrovanih temperatura, ne mozemo "
                              "odrediti maksimalnu temperaturu");
    }
    return *std::max_element(temperature, temperature + broj_temperatura);
  }

  void Ispisi() const;
};
Temperature &Temperature::operator=(const Temperature &t) {
  if (this == &t)
    return *this;

  double *temp = new double[t.velicina];

  for (int i = 0; i < t.broj_temperatura; i++) {
    temp[i] = t.temperature[i];
  }
  delete[] temperature;

  temperature = temp;
  velicina = t.velicina;
  broj_temperatura = t.broj_temperatura;

  return *this;
}

Temperature::Temperature(const Temperature &t)
    : velicina(t.velicina), broj_temperatura(t.broj_temperatura),
      temperature(new double[t.velicina]) {
  for (int i = 0; i < broj_temperatura; i++) {
    temperature[i] = t.temperature[i];
  }
}

void Temperature::Ispisi() const {
  double *nove_temperature = new double[broj_temperatura];
  std::copy(temperature, temperature + broj_temperatura, nove_temperature);
  std::sort(nove_temperature, nove_temperature + broj_temperatura,
            [](double temp1, double temp2) { return temp1 > temp2; });

  for (int i = 0; i < broj_temperatura; i++)
    std::cout << nove_temperature[i] << "\n";

  delete[] nove_temperature;
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