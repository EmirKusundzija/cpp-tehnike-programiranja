#include <iostream>
#include <list>

template <typename IterTip> auto AritmetickaSredina(IterTip p1, IterTip p2) {
  auto suma = *p1;
  suma = 0;
  double br_elemenata = 0;

  while (p1 != p2) {
    suma += *p1;
    p1++;
    br_elemenata++;
  }

  return suma / br_elemenata;
}

template <typename IterTip> auto UzmiVecuPolovicu(IterTip p1, IterTip p2) {
  int br_elemenata = 0;
  auto temp = p1;

  while (temp != p2) {
    temp++;
    br_elemenata++;
  }
  auto sredina = p1;
  int polovina = br_elemenata / 2;

  while (polovina--) {
    sredina++;
  };

  auto as_1 = AritmetickaSredina(p1, sredina);
  auto as_2 = AritmetickaSredina(sredina, p2);
  return as_1 > as_2 ? as_1 : as_2;
}

int main() {

  std::list<int> test(9);

  for (auto &x : test) {
    std::cin >> x;
  }
  auto uzmi_veci = UzmiVecuPolovicu(test.begin(), test.end());

  std::cout << "Veca polovica je: " << uzmi_veci;

  return 0;
}