#include <iostream>
#include <stdexcept>

class Student {
  int indeks = 0;
  int br_polozenih_ispita = 0;
  double prosjek = 5;
  int godina_studija = 1;

public:
  int DajIndeks() const { return indeks; }
  int DajBrojPolozenih() const { return br_polozenih_ispita; }
  double DajProsjek() const { return prosjek; }
  int DajGodinu() const { return godina_studija; }
  void PostaviIndeks(int Indeks) {
    if (Indeks < 0)
      throw std::domain_error("Neispravan broj indeksa");
    indeks = Indeks;
  }

  void RegistrirajOcjenu(int ocjena) {
    if (ocjena < 5 || ocjena > 10)
      throw std::domain_error("Neispravna ocjena");

    if (ocjena == 5)
      return;

    prosjek =
        (prosjek * br_polozenih_ispita + ocjena) / (br_polozenih_ispita + 1);

    br_polozenih_ispita++;
  }

  void ProvjeriGodinu(int broj_predmeta) {
    if (br_polozenih_ispita >= broj_predmeta) {
      std::cout << "Student sa indexom " << indeks << " je uspjesno polozio "
                << godina_studija << ". godinu studija sa prosjekom " << prosjek
                << ", te prelazi na " << godina_studija + 1
                << ". godinu studija." << "\n";

      br_polozenih_ispita = 0;
      prosjek = 5;
      godina_studija++;
    } else {
      std::cout << "Student sa indexom " << indeks
                << " nije ostvario uslov za prelazak na " << godina_studija + 1
                << ". godinu studija." << "\n";
    }
  }
};

int main() {
  Student s;

  std::cout << "Pocetno stanje: " << "\n";

  std::cout << s.DajIndeks() << " " << s.DajBrojPolozenih() << " "
            << s.DajProsjek() << " " << s.DajGodinu() << "\n";

  s.PostaviIndeks(20272);
  // I semestar
  s.RegistrirajOcjenu(7);
  s.RegistrirajOcjenu(7);
  s.RegistrirajOcjenu(6);
  // II semestar
  s.RegistrirajOcjenu(6);
  s.RegistrirajOcjenu(9);
  s.RegistrirajOcjenu(10);

  std::cout << "Status studenta (nakon I i II semestra): " << "\n";

  std::cout << "Indeks: " << s.DajIndeks() << "\n";
  std::cout << "Broj polozenih ispita: " << s.DajBrojPolozenih() << "\n";
  std::cout << "Prosjek: " << s.DajProsjek() << "\n";
  std::cout << "Godina: " << s.DajGodinu() << "\n";

  s.ProvjeriGodinu(6);
  // provjera sa ocjenom 5 (nepolozenim ispitom)
  s.RegistrirajOcjenu(10);
  s.RegistrirajOcjenu(5);
  s.RegistrirajOcjenu(8);
  s.ProvjeriGodinu(3);

  std::cout << "Izuzeci: \n";
  try {
    s.PostaviIndeks(-100);
  } catch (std::domain_error &izuzetak) {
    std::cout << "Greska: " << izuzetak.what() << "!\n";
  }

  try {
    s.RegistrirajOcjenu(399);
  } catch (std::domain_error &izuzetak) {
    std::cout << "Greska: " << izuzetak.what() << "!\n";
  }

  return 0;
}