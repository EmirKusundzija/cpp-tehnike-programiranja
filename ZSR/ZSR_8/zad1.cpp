#include <iostream>
#include <string>
const int BrojRoba = 3;

struct Roba {
  std::string naziv_robe;
  int br_skladista;
  int kolicina_robe;
  int min_kolicina{10};
  int cijena_robe;
  std::string ime_dobavljaca;
};

int main() {
  Roba *robe = new Roba[BrojRoba];

  for (int i = 0; i < BrojRoba; i++) {
    std::cout << "Unesite " << i + 1 << ". naziv robe: ";
    std::getline(std::cin, robe[i].naziv_robe);

    std::cout << "Unesite " << i + 1 << ". broj skladista: ";
    std::cin >> robe[i].br_skladista;

    std::cout << "Unesite " << i + 1 << ". kolicinu robe: ";
    std::cin >> robe[i].kolicina_robe;

    std::cout << "Unesite " << i + 1 << ". cijenu robe: ";
    std::cin >> robe[i].cijena_robe;

    std::cin.clear();
    std::cin.ignore(10000, '\n');

    std::cout << "Unesite " << i + 1 << ". ime dobavljaca: ";
    std::getline(std::cin, robe[i].ime_dobavljaca);
  }
  // Ispis
  for (int i = 0; i < BrojRoba; i++) {
    std::cout << "Naziv robe: " << robe[i].naziv_robe << "\n";
    std::cout << "Broj skladista: " << robe[i].br_skladista << "\n";
    std::cout << "Kolicina robe: " << robe[i].kolicina_robe << "\n";
    if (robe[i].kolicina_robe <= robe[i].min_kolicina) {
      std::cout << "Ime dobavljaca: " << robe[i].ime_dobavljaca << "\n";
    }
  }

  // OBAVEZNO, inace ode memorija u helac
  delete[] robe;
  return 0;
}
