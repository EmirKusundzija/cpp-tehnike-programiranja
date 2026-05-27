#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>


class Kasa {
  int novcanice[11];
  static constexpr int apoeni_pf[11]{5,    10,   20,   50,    100,  500,
                                     1000, 2000, 5000, 10000, 20000};
  static constexpr double apoeni_km[11]{
      0.05, 0.10, 0.20, 0.50, 1.00, 5.00, 10.00, 20.00, 50.00, 100.00, 200.00};

public:
  Kasa() {
    for (int i = 0; i < 11; i++)
      novcanice[i] = 0;
  }
  Kasa(const std::vector<int> &stanje_novcanica) {
    if (stanje_novcanica.size() > 11)
      throw std::domain_error("Vektor ima vise elemenata nego sto ima apoena");
    for (int i = 0; i < 11; i++)
      novcanice[i] = 0;
    for (int i = 0; i < stanje_novcanica.size(); i++) {
      novcanice[i] = stanje_novcanica[i];
    }
  }

  void DodajUKasu(int apoen, int kolicina_novcanica) {
    novcanice[apoen] += kolicina_novcanica;
  }
  void OduzmiIzKase(int apoen, int kolicina_novcanica) {
    if (novcanice[apoen] < kolicina_novcanica)
      throw std::logic_error("Nedovoljno novcanica");
    novcanice[apoen] -= kolicina_novcanica;
  }

  double DajKusur(double iznos) {
    int preostalo_pf = int(std::round(iznos * 100));
    int kusur_pf = 0;

    for (int i = 10; i >= 0 && preostalo_pf > 0; i--) {
      int koliko = std::min(preostalo_pf / apoeni_pf[i], novcanice[i]);
      kusur_pf += koliko * apoeni_pf[i];
      novcanice[i] -= koliko;
      preostalo_pf -= koliko * apoeni_pf[i];
    }

    return kusur_pf / 100.0;
  }

  void IspisiStanjeKase(bool ispisi_sve = false) const {
    int stanje_pf = 0;
    for (int i = 0; i < 11; i++)
      stanje_pf += novcanice[i] * apoeni_pf[i];

    std::cout << "Trenutno se u kasi nalazi " << std::fixed
              << std::setprecision(2) << stanje_pf / 100.0 << "KM\n";

    if (ispisi_sve) {
      for (int i = 0; i < 11; i++)
        std::cout << apoeni_km[i] << " - " << novcanice[i] << "\n";
    }
  }
};

constexpr int Kasa::apoeni_pf[11];
constexpr double Kasa::apoeni_km[11];

int main() {

  try {
    Kasa k1;
    k1.IspisiStanjeKase();

    std::vector<int> pocetno_stanje{0, 5, 10, 2, 16, 10, 3, 10, 10, 1, 0};

    // probajmo
    // Kasa k2({0,5,10,2,16,10,3,10,10,1,0});

    Kasa k2(pocetno_stanje);

    k2.IspisiStanjeKase(true);

    k2.DodajUKasu(4, 5);
    k2.IspisiStanjeKase();

    k2.OduzmiIzKase(4, 3);
    k2.IspisiStanjeKase();

    double kusur = k2.DajKusur(15.5);
    std::cout << "Vraceni kusur: " << std::fixed << std::setprecision(2)
              << kusur << " KM\n";
    k2.IspisiStanjeKase(true);

    // izuzeci
    try {
      k2.OduzmiIzKase(9, 10);
    } catch (std::logic_error &i) {
      std::cout << "Uhvaceno: " << i.what() << "!\n";
    }

    try {
      std::vector<int> overflow(15, 1);
      Kasa k3(overflow);
    } catch (std::exception &izuzetak) {
      std::cout << "GRESKA: " << izuzetak.what() << "!\n";
    }
  } catch (std::exception &izuzetak) {
    std::cout << "GRESKA: " << izuzetak.what() << "!\n";
  }

  return 0;
}