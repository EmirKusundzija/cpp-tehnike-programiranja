// TP 2025/2026: Zadaća 1, Zadatak 3
#include <deque>
#include <iomanip>
#include <iostream>
#include <stdexcept>

typedef std::deque<std::deque<int>> Matrica;

Matrica KreirajMatricu(int br_redova, int br_kolona) {
  return Matrica(br_redova, std::deque<int>(br_kolona));
}

Matrica UnesiMatricu(int br_redova, int br_kolona) {
  auto m = KreirajMatricu(br_redova, br_kolona);
  for (int i = 0; i < br_redova; i++) {
    for (int j = 0; j < br_kolona; j++) {
      std::cin >> m.at(i).at(j);
    }
  }
  return m;
}

Matrica EkspanzijaMatrice(Matrica A, int p, int q) {

  if (p <= 0 || q <= 0)
    throw std::domain_error("Nelegalni parametri");
  if (A.size() == 0 || A.at(0).size() == 0)
    throw std::domain_error("Nekorektna matrica");
  for (int i = 1; i < A.size(); i++) {
    if (A.at(i).size() != A.at(0).size())
      throw std::domain_error("Nekorektna matrica");
  }

  int br_redova = A.size();
  int br_kolona = A.at(0).size();

  auto rezultat = KreirajMatricu(br_redova * p, br_kolona * q);

  for (int i = 0; i < A.size(); i++)

    for (int j = 0; j < A.at(0).size(); j++) {
      for (int red = 0; red < p; red++)
        for (int kolona = 0; kolona < q; kolona++) {
          rezultat.at(i * p + red).at(j * q + kolona) = A.at(i).at(j);
        }
    }

  return rezultat;
}

void IspisiMatricu(Matrica m) {
  for (int i = 0; i < m.size(); i++) {
    for (int j = 0; j < m.at(i).size(); j++) {
      std::cout << std::setw(6) << m.at(i).at(j);
    }
    std::cout << "\n";
  }
}

int main() {
  try {
    int m, n;

    std::cout << "Unesite broj redova i kolona matrice: ";
    std::cin >> m >> n;

    std::cout << "Unesite elemente matrice: \n";
    Matrica A = UnesiMatricu(m, n);
    int p, q;
    std::cout << "Unesite p i q: ";
    std::cin >> p >> q;
    Matrica ekspanzija = EkspanzijaMatrice(A, p, q);
    std::cout << "\n";
    std::cout << p << "x" << q << " ekspanzija zadane matrice glasi:\n";
    IspisiMatricu(ekspanzija);
  } catch (std::domain_error izuzetak) {
    std::cout << "GRESKA: " << izuzetak.what() << "!\n";
  }
  return 0;
}
