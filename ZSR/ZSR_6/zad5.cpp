#include <iostream>
#include <vector>

double *NizVektor(std::vector<double> &v) {
  double *niz = new double[v.size()];
  for (int i = 0; i < v.size(); i++) {
    niz[i] = 1. / v.at(i);
  }

  return niz;
}

int main() {
  std::vector<double> v{0.3, -0.5, 1e-3, 1e-22};
  std::cout << "Originalan sadrzaj vektora: ";

  for (auto &x : v) {
    std::cout << x << " ";
  }
  double *niz_nesto = NizVektor(v);

  std::cout << "\nSadrzaj niza: ";
  for (int i = 0; i < v.size(); i++) {
    std::cout << niz_nesto[i] << " ";
  }
  std::cout << "\n";
  delete[] niz_nesto;
  return 0;
}