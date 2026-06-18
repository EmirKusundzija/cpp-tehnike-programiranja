#include <iostream>

template <typename T> class Vektor {
  T *elementi;
  int kapacitet, velicina;
  void Realociraj(int novi_kapacitet) {
    T *novi = nullptr;
    try {
      novi = new T[novi_kapacitet];
      for (int i{}; i < velicina; i++) {
        novi[i] = elementi[i];
      }
    } catch (...) {
      delete[] novi;
      throw;
    }
    delete[] elementi;
    elementi = novi;
    kapacitet = novi_kapacitet;
  }

public:
  Vektor() : elementi(new T[10]), kapacitet(10), velicina(0) {}
  ~Vektor() { delete[] elementi; }
  Vektor(const Vektor &drugi)
      : kapacitet(drugi.kapacitet), velicina(drugi.velicina) {
    elementi = new T[kapacitet];
    std::copy(drugi.elementi, drugi.elementi + velicina, elementi);
  }
  Vektor &operator=(const Vektor &drugi) {
    if (this != &drugi) {
      delete[] elementi;
      kapacitet = drugi.kapacitet;
      velicina = drugi.velicina;
      elementi = new T[kapacitet];
      std::copy(drugi.elementi, drugi.elementi + velicina, elementi);
    }
    return *this;
  }
  Vektor(Vektor &&drugi)
      : elementi(drugi.elementi), kapacitet(drugi.kapacitet),
        velicina(drugi.velicina) {
    drugi.velicina = drugi.kapacitet = 0;
    drugi.elementi = nullptr;
  }
  Vektor &operator=(Vektor &&drugi) {
    if (this != &drugi) {
      delete[] elementi;

      elementi = drugi.elementi;
      kapacitet = drugi.kapacitet;
      velicina = drugi.velicina;
      drugi.velicina = drugi.kapacitet = 0;
      drugi.elementi = nullptr;
    }
    return *this;
  }
  void DodajNaKraj(const T &element) {
    if (velicina == kapacitet)
      Realociraj(kapacitet + kapacitet / 2);
    elementi[velicina] = element;
    velicina++;
  }
  T &at(int indeks) {
    if (indeks < 0 || indeks >= velicina)
      throw std::out_of_range("Nevaljan pristup");
    return elementi[indeks];
  }
  const T &at(int indeks) const {
    if (indeks < 0 || indeks >= velicina)
      throw std::out_of_range("Nevaljan pristup");

    return elementi[indeks];
  }
  int DajVelicinu() const { return velicina; }
  T &operator[](int indeks) { return at(indeks); }
  const T &operator[](int indeks) const { return at(indeks); }
};

int main() { return 0; }
