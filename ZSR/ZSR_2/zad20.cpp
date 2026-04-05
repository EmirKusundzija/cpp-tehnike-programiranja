#include <iostream>
#include <vector>

int SumaCifara(int n) {
  int suma = 0;
  while (n > 0) {
    int cifra = n % 10;
    n /= 10;
    suma += cifra;
  }
  return suma;
}

std::vector<int> VecSumaCifara(std::vector<int> brojevi) {
  std::vector<int> rez;
  for (int i : brojevi) {
    rez.push_back(SumaCifara(i));
  }
  return rez;
}

int main() {

  int n;
  std::cout << "Unesite n: ";
  std::cin >> n;

  std::vector<int> brojevi;
  for (int i = 0; i < n; i++) {
    int broj;
    std::cout << "Unesite " << i + 1 << ". broj: ";
    std::cin >> broj;
    brojevi.push_back(broj);
  }

  std::vector<int> suma_cifara = VecSumaCifara(brojevi);

  for (int i = 0; i < suma_cifara.size(); i++) {
    std::cout << suma_cifara.at(i) << " ";
  }
  return 0;
}