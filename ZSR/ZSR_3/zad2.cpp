#include <iostream>
#include <vector>

typedef std::vector<std::vector<int>> Matrica;

Matrica KreirajMatricu(int br_redova, int br_kolona) {
  return Matrica(br_redova, std::vector<int>(br_kolona));
}

int BrojRedova(Matrica m) { return m.size(); }
int BrojKolona(Matrica m) { return m.size() != 0 ? m[0].size() : 0; }

Matrica UnesiMatricu(int br_redova, int br_kolona) {
  auto m = KreirajMatricu(br_redova, br_kolona);
  for (int i = 0; i < br_redova; i++)
    for (int j = 0; j < br_kolona; j++) {
      std::cout << "Element (" << i + 1 << "," << j + 1 << "): ";
      std::cin >> m[i][j];
    }
  return m;
}

void IspisiMatricu(Matrica m) {

  for (int i = 0; i < BrojRedova(m); i++)
    for (int j = 0; j < BrojKolona(m); j++) {
      std::cout << m[i][j];
    }
  std::cout << "\n";
}

int main() {

  int n;

  std::cout << "Unesite n: ";
  std::cin >> n;

  auto matrica = UnesiMatricu(n, n);
  IspisiMatricu(matrica);
  int suma = 0;
  for (int i = 0; i < BrojRedova(matrica); i++)
    for (int j = 0; j < BrojKolona(matrica); j++) {
      if (i == j)
        suma += matrica.at(i).at(i);
    }

  return 0;
}