#include <iostream>

int main() {
  int brzina_broda;
  std::cout << "Unesite brzinu broda u cvorovima: ";
  std::cin >> brzina_broda;

  const int morska_milja = 1852;

  double brzina_broda_kmh =
      static_cast<double>(brzina_broda) * morska_milja / 1000;
  std::cout << "Brzina broda u km/h iznosi: " << brzina_broda_kmh << std::endl;
  return 0;
}