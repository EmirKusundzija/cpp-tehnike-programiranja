#include <algorithm>
#include <initializer_list>
#include <iostream>
template <typename T> class Dek {

  int kapacitet;
  T **elementi;
  int i1, i2;
  void Realociraj() {
    T **novi = nullptr;
    int velicina = i2 - i1;
    int novi_kapacitet = kapacitet + kapacitet / 2;
    int novi_i1 = novi_kapacitet / 3;
    try {
      novi = new T *[novi_kapacitet];
      for (int i{}; i < velicina; i++)
        novi[novi_i1 + i] = elementi[i1 + i];
    } catch (...) {
      delete[] novi;
      throw;
    }
    delete[] elementi;
    elementi = novi;
    i1 = novi_i1;
    i2 = novi_i1 + velicina;
    kapacitet = novi_kapacitet;
  }

public:
  Dek() : kapacitet(10), elementi(new T *[10]{}), i1(5), i2(5) {}
  ~Dek() {
    for (int i{i1}; i < i2; i++)
      delete elementi[i];
    delete[] elementi;
  }
  Dek &operator=(Dek &&d) {
    if (this != &d) {
      for (int i{i1}; i < i2; i++)
        delete elementi[i];
      delete[] elementi;

      kapacitet = d.kapacitet;
      elementi = d.elementi;
      i1 = d.i1;
      i2 = d.i2;

      d.i2 = 0;
      d.i1 = 0;
      d.kapacitet = 0;
      d.elementi = nullptr;
    }
    return *this;
  }
  Dek(Dek &&d)
      : kapacitet(d.kapacitet), elementi(d.elementi), i1(d.i1), i2(d.i2) {
    d.i2 = d.i1 = d.kapacitet = 0;
    d.elementi = nullptr;
  }
  Dek(const Dek &d)
      : i1(d.i1), i2(d.i2), kapacitet(d.kapacitet),
        elementi(new T *[d.kapacitet]) {
    for (int i = i1; i < i2; i++)
      elementi[i] = new T(*d.elementi[i]);
  }
  Dek &operator=(const Dek &d) {
    if (this != &d) {
      for (int i = i1; i < i2; i++)
        delete elementi[i];
      delete[] elementi;
      i1 = d.i1;
      i2 = d.i2;
      kapacitet = d.kapacitet;
      elementi = new T *[kapacitet];
      for (int i = i1; i < i2; i++)
        elementi[i] = new T(*d.elementi[i]);
    }
    return *this;
  }
  Dek(std::initializer_list<T> lista) : Dek() {
    for (auto &e : lista) {
      DodajNaKraj(e);
    }
  }
  const T &operator[](int indeks) const { return *elementi[indeks + i1]; }
  T &operator[](int indeks) { return *elementi[indeks + i1]; }

  void DodajNaKraj(const T &element) {
    if (i2 >= kapacitet)
      Realociraj();

    elementi[i2] = new T(element);
    i2++;
  }
  void DodajNaPocetak(const T &element) {
    if (i1 <= 0)
      Realociraj();
    i1--;
    elementi[i1] = new T(element);
  }
  void Ispisi() const {
    std::for_each(elementi + i1, elementi + i2,
                  [](const T *element) { std::cout << *element << " "; });
  }
  int DajVelicinu() const { return i2 - i1; }
};

int main() {
  Dek<double> a;

  a.DodajNaKraj(2);
  a.DodajNaKraj(5.2);
  a.DodajNaPocetak(89);
  std::cout << a[2];
  return 0;
}
