#include <iostream>
#include <vector>

bool SumaCifaraParnoNeparno(int n) {
  int temp = std::abs(n);
  int suma = 0;
  while (temp > 0) {
    int cifra = temp % 10;
    temp /= 10;
    suma += cifra;
  }

  return suma % 2 == 0;
}

void IspisiVektor(std::vector<int> v) {
  for (int i = 0; i < v.size(); i++) {
    std::cout << v.at(i);
    if (i != v.size() - 1)
      std::cout << ",";
  }
}

std::vector<int> IzdvojiElemente(std::vector<int> br, bool par_nepar) {
  std::vector<int> rez;
  for (auto x : br) {
    if (SumaCifaraParnoNeparno(x) == par_nepar)
      rez.push_back(x);
  }
  return rez;
}

int main() {
  int n;
  std::cout << "Koliko zelite unijeti elemenata: ";
  std::cin >> n;

  std::vector<int> vec(n);
  std::cout << "Unesite elemente: ";
  for (int i = 0; i < n; i++) {
    std::cin >> vec.at(i);
  }
  auto vec_parni = IzdvojiElemente(vec, true);
  auto vec_neparni = IzdvojiElemente(vec, false);

  if (vec_parni.empty())
    std::cout << "---";
  IspisiVektor(vec_parni);
  std::cout << "\n";

  if (vec_neparni.empty())
    std::cout << "---";
  IspisiVektor(vec_neparni);
  std::cout << "\n";
  return 0;
}