// TP 2025/2026: Zadaća 2, Zadatak 4
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

template <typename Tip> using Matrica = std::vector<std::vector<Tip>>;

template <typename Tip> void IspisiMatricu(std::vector<std::vector<Tip>> &mat) {
  for (int i = 0; i < mat.size(); i++) {
    for (int j = 0; j < mat.at(i).size(); j++) {
      std::cout << mat.at(i).at(j) << " ";
    }
    std::cout << "\n";
  }
}
template <typename Tip>
bool Kriterij(std::vector<Tip> v1, std::vector<Tip> v2) {
  Tip proizvod_1 = 1;
  for (const auto &i : v1) {
    proizvod_1 *= i;
  }
  Tip proizvod_2 = 1;
  for (const auto &j : v2) {
    proizvod_2 *= j;
  }
  if (proizvod_1 != proizvod_2)
    return proizvod_1 < proizvod_2;
  return v1 < v2;
}

template <typename ProizvoljanTip>
void SortirajPoProizvoduRedova(
    std::vector<std::vector<ProizvoljanTip>> &matrica) {
  std::sort(matrica.begin(), matrica.end(), Kriterij<ProizvoljanTip>);
}

int main() {
  std::cout
      << "Unesite elemente (* za kraj reda, * na pocetku reda za kraj unosa): ";
  Matrica<int> A{};

  for (;;) {
    std::vector<int> red;

    int broj;
    while (std::cin >> broj) {
      red.push_back(broj);
    }
    std::cin.clear();

    char ne_broj;
    std::cin >> ne_broj;
    if (red.empty())
      break;

    A.push_back(red);
  }

  std::cout << "\nMatrica nakon sortiranja: \n";
  SortirajPoProizvoduRedova(A);
  IspisiMatricu(A);

  std::cout << "\n";
  std::cout << "Unesite elemente sekvence koja se trazi (* za kraj reda): ";

  std::vector<int> sekvenca;
  int broj;
  while (std::cin >> broj) {
    sekvenca.push_back(broj);
  }

  auto it = std::lower_bound(A.begin(), A.end(), sekvenca, Kriterij<int>);

  if (it != A.end() && !Kriterij<int>(*it, sekvenca) &&
      !Kriterij<int>(sekvenca, *it)) {
    int indeks = it - A.begin();
    std::cout << "Trazena sekvenca se nalazi u " << indeks + 1
              << ". redu (nakon sortiranja)\n";
  } else
    std::cout << "Trazena sekvenca se ne nalazi u matrici\n";

  return 0;
}
