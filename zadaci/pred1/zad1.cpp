#include <iostream>
int main() {
  int a, b, c;
  std::cout << "Unesite duzinu, sirinu i dubinu bazena u metrima: ";
  std::cin >> a >> b >> c;
  // pretvaranje iz metara u centimetre
  int a_centi = a * 100;
  int b_centi = b * 100;
  int c_centi = c * 100;

  int d;
  std::cout << "Unesite sirinu plocice u centimetrima: ";
  std::cin >> d;

  int povrsina_bazena = 2 * c_centi * (a_centi + b_centi) + a_centi * b_centi;

  if (a_centi % d == 0 && b_centi % d == 0 && c_centi % d == 0) {
    int br_plocica = povrsina_bazena / (d * d);
    std::cout << "Potrebno je " << br_plocica << "plocica." << std::endl;
  } else {
    std::cout << "Poplocavanje bazena dimenzija 5x15x3m s plocicama dimenzija "
                 "13x13cm nije izvodljivo bez lomljenja plocica!"
              << std::endl;
  }

  return 0;
}