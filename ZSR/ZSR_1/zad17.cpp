// ax+b=c

#include <iostream>

double UnesiBroj() {
  double broj;
  while (!(std::cin >> broj)) {
    std::cout << "Neispravan unos. Molimo, pokusajte ponovo.\n";
    std::cin.clear();
    std::cin.ignore(10000, '\n');
  }

  return broj;
}

int main() {
  std::cout << "Unesite a: ";
  double a = UnesiBroj();
  std::cout << "Unesite b: ";
  double b = UnesiBroj();
  std::cout << "Unesite c: ";
  double c = UnesiBroj();

  if (a == 0) {

    if (b == c) {
      std::cout << "Jednacina ax+b=c ima beskonacno mnogo rjesenja.\n";
    } else {
      std::cout << "Jednacina ax+b=c nema rjesenje. a ne smije biti 0.\n";
    }
  } else {
    double x = (-b + c) / a;
    std::cout << "Rijesenje jednacine ax+b=c je: " << x << "\n";
  }

  // ax+b=c
  // ax+b-c=0
  // ax = -b+c
  // x = (-b+c)/a
  return 0;
}