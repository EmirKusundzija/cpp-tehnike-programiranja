#include <iomanip>
#include <iostream>

int main() {
  int N;
  std::cout << "Unesite n: ";
  std::cin >> N;
  double a;

  double S = 0;
  double suma = 0;
  for (int i = 1; i <= N; i++) {

    double a_i;
    std::cout << "Unesite a(" << i << ") clan: ";
    std::cin >> a_i;

    suma += a_i;
    S += 1.0 / suma;
  }

  std::cout << "Rezultat: " << std::fixed << std::setprecision(3) << S;
  return 0;
}