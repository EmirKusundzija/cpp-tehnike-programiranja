#include <cmath>
#include <iostream>

double Izvod(double (*f)(double), double x, double h = 1e-5) {
  return (f(x + h) - f(x)) / h;
}

int main() {
  std::cout << "Izvod od sinusa u tacki 0 (sin(0))' = " << Izvod(std::sin, 0);

  return 0;
}