#include <cmath>
#include <iostream>
#include <stdexcept>
double f(double x, int n) {

  if (n <= 0)
    throw std::domain_error("N nije prirodan ili je 0.");
  double suma = 0.0;
  for (int i = 0; i <= n; i++) {

    double nazivnik = x * (x + i) - (i % 2 == 0 ? 1 : -1) * i * i;
    if (nazivnik < 0)
      throw std::domain_error("Podkorijena velicina ne moze biti negativna.");

    double brojnik = std::pow(x, i);
    double k_nazivnik = std::sqrt(nazivnik);

    if (k_nazivnik == 0)
      throw std::domain_error("Dijeljenje sa 0 je besmisleno kolega");

    suma += brojnik / k_nazivnik;
  }

  return suma;
}
int main() {
  try {
    for (;;) {
      double x;
      int n;
      std::cout << "Unesite x i n: ";
      std::cin >> x >> n;
      std::cout << "Rezultat: " << f(x, n) << "\n";
    }
  } catch (std::domain_error &e) {
    std::cout << "Greska: " << e.what() << "\n";
  }

  return 0;
}