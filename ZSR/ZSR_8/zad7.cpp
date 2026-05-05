#include <iostream>
#include <string>

struct Cvor {
  std::string lokacija;
  int cijena, kvadratura;
  Cvor *veza;
};

int main() {
  Cvor *poc = nullptr, *prethodni;

  for (;;) {
    int cijena, kvadratura;

    std::string lokacija;
    std::cout << "Unesite lokaciju: ";
    std::getline(std::cin, lokacija);
    if (lokacija == "")
      break;

    std::cout << "Unesite cijenu i kvadraturu: ";
    std::cin >> cijena >> kvadratura;
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    Cvor *novi = new Cvor{lokacija, cijena, kvadratura};
    if (!poc)
      poc = novi;
    else if (novi->cijena < poc->cijena ||
             novi->cijena == poc->cijena &&
                 novi->kvadratura > poc->kvadratura) {
      novi->veza = poc;
      poc = novi;
    } else
      prethodni->veza = novi;
    prethodni = novi;
  }

  for (Cvor *p = poc; p != nullptr; p = p->veza) {
    std::cout << p->lokacija << " " << p->cijena << "KM, " << p->kvadratura
              << "m^2\n";
  }

  return 0;
}
