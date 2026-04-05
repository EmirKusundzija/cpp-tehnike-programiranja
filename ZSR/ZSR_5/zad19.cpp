#include <cmath>
#include <iostream>

double Simpson(double (*f)(double), double a, double b, int n) {
  double h = (b - a) / n; // duzina podintervala;

  double suma1 = 0;
  for (int k = 1; k <= n - 1; k += 2) {
    suma1 += f(a + k * h);
  }

  double suma2 = 0;
  for (int k = 2; k <= n - 2; k += 2) {
    suma2 += f(a + k * h);
  }

  double rezultat_simpsona = (h / 3.) * (f(a) + 4 * suma1 + 2 * suma2 + f(b));

  return rezultat_simpsona;
}

int main() {

  std::cout << "Integral sin(x) (0,pi): "
            << Simpson(std::sin, 0, std::atan(1) * 4, 100);
  std::cout << "\n";
  std::cout << "Integral x*x*x (0,10): "
            << Simpson([](double x) { return x * x * x; }, 0, 10, 100);
  std::cout << "\n";
  std::cout << "Integral 1/x (1,2): "
            << Simpson([](double x) { return 1. / x; }, 1, 2, 100);
  std::cout << "\n";
  return 0;
}