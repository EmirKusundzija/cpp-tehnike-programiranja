// TP 2025/2026: Zadaća 2, Zadatak 5
#include <deque>
#include <iostream>
#include <stdexcept>

// pomocne funkcije za alokaciju (i dealokaciju) grbave matrice
template <typename TipElemenata>
void DealocirajMatricu(TipElemenata **mat, int br_redova) {
  if (!mat)
    return;
  if (br_redova > 0)
    delete[] mat[0];

  delete[] mat;
}

template <typename TipElemenata>
TipElemenata **StvoriGrbavuMatricu(int br_redova) {
  TipElemenata **mat = nullptr;
  try {
    mat = new TipElemenata *[br_redova] {};
    if (br_redova > 0) {
      mat[0] = new TipElemenata[br_redova * (br_redova + 1) / 2];
      for (int i = 1; i < br_redova; i++)
        mat[i] = mat[i - 1] + i;
    }
  } catch (...) {
    DealocirajMatricu(mat, br_redova);
    throw std::range_error("Nema dovoljno memorije");
  }

  return mat;
}

template <typename IterTip, typename FunTip>
auto KreirajFunkcijskuTablicu(IterTip p1, IterTip p2, FunTip f) {
  using RezTip = decltype(f(*p1, *p1));
  int br_redova = 0;
  IterTip it_temp = p1;
  while (it_temp != p2) {
    br_redova++;
    it_temp++;
  }

  RezTip **mat = StvoriGrbavuMatricu<RezTip>(br_redova);

  IterTip it_red = p1;
  for (int i = 0; i < br_redova; i++, it_red++) {
    IterTip it_kolona = p1;
    for (int j = 0; j <= i; j++, it_kolona++) {
      RezTip lijevo, desno;
      try {
        lijevo = f(*it_red, *it_kolona);
        desno = f(*it_kolona, *it_red);
      } catch (...) {
        DealocirajMatricu(mat, br_redova);
        throw std::runtime_error("Neocekivani problemi pri racunanju");
      }
      if (lijevo != desno) {
        DealocirajMatricu(mat, br_redova);
        throw std::logic_error("Pretpostavka o komutativnosti nije ispunjena");
      }
      mat[i][j] = lijevo;
    }
  }

  return mat;
}

int main() {
  int duzina;
  std::cout << "Duzina sekvence: ";
  std::cin >> duzina;

  std::deque<double> sekvenca(duzina);
  std::cout << "Elementi sekvence: ";
  for (auto &x : sekvenca) {
    std::cin >> x;
  }

  try {
    auto matrica =
        KreirajFunkcijskuTablicu(sekvenca.begin(), sekvenca.end(),
                                 [](double x, double y) { return x * y; });

    std::cout << "Tablica mnozenja:\n";
    for (int i = 0; i < duzina; i++) {
      for (int j = 0; j <= i; j++) {
        std::cout << matrica[i][j] << " ";
      }
      std::cout << "\n";
    }
    DealocirajMatricu(matrica, duzina);
  } catch (std::exception &e) {
    std::cout << "GRESKA: " << e.what() << "!\n";
  }

  return 0;
}
