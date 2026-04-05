#include <deque>
#include <iostream>

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

void IspisiDek(std::deque<int> v) {
  for (int i = 0; i < v.size(); i++) {
    std::cout << v.at(i);
    if (i != v.size() - 1)
      std::cout << ",";
  }
}

std::deque<int> IzdvojiElemente(std::deque<int> br, bool par_nepar) {
  std::deque<int> rez;
  for (int i = br.size() - 1; i >= 0; i--) {
    if (SumaCifaraParnoNeparno(br.at(i)) == par_nepar)
      rez.push_front(br.at(i));
  }
  return rez;
}

int main() {
  int n;
  std::cout << "Koliko zelite unijeti elemenata: ";
  std::cin >> n;

  std::deque<int> dek(n);
  std::cout << "Unesite elemente: ";
  for (int i = 0; i < n; i++) {
    std::cin >> dek.at(i);
  }
  auto dek_parni = IzdvojiElemente(dek, true);
  auto dek_neparni = IzdvojiElemente(dek, false);

  if (dek_parni.empty())
    std::cout << "---";
  IspisiDek(dek_parni);
  std::cout << "\n";

  if (dek_neparni.empty())
    std::cout << "---";
  IspisiDek(dek_neparni);
  std::cout << "\n";
  return 0;
}