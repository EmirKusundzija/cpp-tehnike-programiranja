#include <iostream>
#include <stdexcept>
#include <string>

class Student {
  std::string ime{""};
  std::string prezime{""};
  int indeks{0};
  int godina_studija{1};
  int ocjene[10]{
      5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
  };

public:
  void PostaviStudenta(std::string ime, std::string prezime, int indeks) {
    if (indeks < 0)
      throw std::domain_error("Indeks ne moze biti negativan");
    this->ime = ime;
    this->prezime = prezime;
    this->indeks = indeks;
  }
  std::string DajIme() const { return ime; }
  std::string DajPrezime() const { return prezime; }
  int DajIndeks() const { return indeks; }
  int DajGodinuStudija() const { return godina_studija; }
  bool ImaLiProlaz() const {
    int br_petica{0};

    for (int i{0}; i < 10; i++) {
      if (ocjene[i] == 5)
        br_petica++;
    }
    if (br_petica <= 1)
      return true;
    return false;
  }

  void PostaviOcjenu(int broj_kursa, int ocjena) {
    if (broj_kursa < 1 || broj_kursa > 10)
      throw std::domain_error("Nevazeci broj kursa");
    if (ocjena < 5 || ocjena > 10)
      throw std::domain_error("Nevazeca ocjena");

    ocjene[broj_kursa - 1] = ocjena;
  }

  int DajOcjenu(int broj_kursa) const {
    if (broj_kursa < 1 || broj_kursa > 10)
      throw std::domain_error("Nevazeci broj kursa");
    return ocjene[broj_kursa - 1];
  }
  double DajProsjek() const {
    int broj_prolaznih_predmeta{0};

    double suma{0.0};
    for (int i{0}; i < 10; i++) {
      if (ocjene[i] != 5) {
        suma += ocjene[i];
        broj_prolaznih_predmeta++;
      }
    }

    if (broj_prolaznih_predmeta == 0)
      return 5;
    return suma / broj_prolaznih_predmeta;
  }
  void PredjiNaSljedecuGodinu() {
    godina_studija++;
    for (int i = 0; i < 10; i++)
      ocjene[i] = 5;
  }
  bool DaLiJeBoljiOd(const Student &s1) const {
    return DajProsjek() > s1.DajProsjek();
  }
  static bool DaLiJePrviBolji(const Student &s1, const Student &s2) {
    return s1.DajProsjek() > s2.DajProsjek();
  }

  void Ispisi() const {
    std::cout << "Ime i prezime: " << ime << " " << prezime << "\n";
    std::cout << "Ocjene: ";
    for (int i = 0; i < 10; i++) {

      std::cout << ocjene[i];
      if (i != 9)
        std::cout << ", ";
    }

    std::cout << "\nIndeks: " << indeks << "\n";
    std::cout << "Godina studija: " << godina_studija << "\n";
    std::cout << "Je li uspjesan? " << (ImaLiProlaz() ? "Jeste" : "Nije")
              << "!\n";
    std::cout << "Prosjek: " << DajProsjek() << "\n";
  }
};

int main() {

  Student s1, s2;

  s1.PostaviStudenta("Emir", "Kusundzija", 20272);

  // I semestar za s1
  s1.PostaviOcjenu(1, 6);
  s1.PostaviOcjenu(2, 6);
  s1.PostaviOcjenu(3, 8);
  s1.PostaviOcjenu(4, 7);
  s1.PostaviOcjenu(5, 6);
  // II semestar za s1
  s1.PostaviOcjenu(6, 7);
  s1.PostaviOcjenu(7, 10); // aBd
  s1.PostaviOcjenu(8, 8);
  s1.PostaviOcjenu(9, 9);
  s1.PostaviOcjenu(10, 6);

  s1.Ispisi();

  std::cout << "---------------------------\n";
  s2.PostaviStudenta("Amna", "Amnic", 20310);
  // I semestar za s2
  s2.PostaviOcjenu(1, 6);
  s2.PostaviOcjenu(2, 6);
  s2.PostaviOcjenu(3, 7);
  s2.PostaviOcjenu(4, 6);
  s2.PostaviOcjenu(5, 6);
  // II semestar za s2
  s2.PostaviOcjenu(6, 7);
  s2.PostaviOcjenu(7, 5);
  s2.PostaviOcjenu(8, 8);
  s2.PostaviOcjenu(9, 6);
  s2.PostaviOcjenu(10, 6);

  s2.Ispisi();

  std::cout << "-----------------------\n";

  std::cout << "Da li je s1 bolji od s2? "
            << (s1.DaLiJeBoljiOd(s2) ? "Da" : "Ne") << "\n";

  std::cout << "Da li je prvi bolji? "
            << (Student::DaLiJePrviBolji(s1, s2) ? "Da" : "Ne") << "\n";

  s1.PredjiNaSljedecuGodinu();
  s2.PredjiNaSljedecuGodinu();

  s1.Ispisi();
  s2.Ispisi();

  // Izuzeci
  std::cout << "\n";

  try {
    Student problematican;
    problematican.PostaviStudenta("Janko", "Kesic", -1);
    problematican.Ispisi();
  } catch (std::domain_error &e) {
    std::cout << e.what() << "!\n";
  }

  try {
    Student problematican;
    problematican.PostaviStudenta("Mirko", "Keksic", 10023);
    // ispravna ocjena, neispravan kurs
    problematican.PostaviOcjenu(200, 10);

  } catch (std::domain_error &e) {
    std::cout << e.what() << "!\n";
  }

  try {
    Student problematican;
    problematican.PostaviStudenta("Mirko", "Keksic", 10023);
    // ispravan kurs, neispravna ocjena
    problematican.PostaviOcjenu(4, 111);

  } catch (std::domain_error &e) {
    std::cout << e.what() << "!\n";
  }
  std::cout << "\nTest konstantnog studenta:\n";

  const Student redovan_student;

  std::cout << "Ime: " << redovan_student.DajIme() << "\n";
  std::cout << "Prezime: " << redovan_student.DajPrezime() << "\n";
  std::cout << "Indeks: " << redovan_student.DajIndeks() << "\n";
  std::cout << "Godina studija: " << redovan_student.DajGodinuStudija() << "\n";
  std::cout << "Ocjena iz kursa 1: " << redovan_student.DajOcjenu(1) << "\n";
  std::cout << "Prosjek: " << redovan_student.DajProsjek() << "\n";
  std::cout << "Ima li prolaz: "
            << (redovan_student.ImaLiProlaz() ? "Da" : "Ne") << "\n";

  redovan_student.Ispisi();
  return 0;
}