#include <iostream>
#include <stdexcept>
#include <string>
class Student {
  int indeks;
  std::string ime;

public:
  Student(int indeks, std::string ime) : indeks(indeks), ime(ime) {}
  int DajIndeks() const { return indeks; }
  std::string DajIme() const { return ime; }
};

class Studenti {
  Student **lista_studenata;
  int velicina, kapacitet;
  void Obrisi() {
    for (int i{}; i < velicina; i++) {
      delete lista_studenata[i];
    }
    delete[] lista_studenata;
    lista_studenata = nullptr;
    velicina = 0;
    kapacitet = 0;
  }

public:
  Studenti(int max_velicina)
      : lista_studenata(new Student *[max_velicina] {}),
        kapacitet(max_velicina), velicina(0) {}
  Studenti(Studenti &&s)
      : lista_studenata(s.lista_studenata), velicina(s.velicina),
        kapacitet(s.kapacitet) {
    s.lista_studenata = nullptr;
    s.velicina = 0;
    s.kapacitet = 0;
  }
  Studenti(const Studenti &s)
      : lista_studenata(new Student *[s.kapacitet]), velicina(s.velicina),
        kapacitet(s.kapacitet) {
    for (int i = 0; i < velicina; i++) {
      lista_studenata[i] = new Student(*s.lista_studenata[i]);
    }
  }
  Studenti &operator=(const Studenti &s) {
    if (this != &s) {
      Obrisi();
      velicina = s.velicina;
      kapacitet = s.kapacitet;
      lista_studenata = new Student *[kapacitet];
      for (int i{}; i < velicina; i++) {
        lista_studenata[i] = new Student(*s.lista_studenata[i]);
      }
    }
    return *this;
  }
  Studenti &operator=(Studenti &&s) {
    if (this != &s) {
      Obrisi();
      lista_studenata = s.lista_studenata;
      velicina = s.velicina;
      kapacitet = s.kapacitet;

      s.lista_studenata = nullptr;
      s.velicina = 0;
      s.kapacitet = 0;
    }
    return *this;
  }
  ~Studenti() { Obrisi(); }
};

int main() { return 0; }