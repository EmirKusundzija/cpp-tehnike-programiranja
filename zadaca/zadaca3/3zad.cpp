// TP 2025/2026: Zadaća 3, Task 3
#include <iomanip>
#include <iostream>
#include <new>
#include <stdexcept>

template <typename TipElemenata> struct Matrica {
  char ime_matrice; // Koristi se samo u funkciji "UnesiMatricu"
  int br_redova, br_kolona;
  TipElemenata **elementi = nullptr; // VEOMA BITNA INICIJALIZACIJA!!!
};

template <typename TipElemenata>
void UnistiMatricu(Matrica<TipElemenata> &mat) {
  if (!mat.elementi)
    return;
  for (int i = 0; i < mat.br_redova; i++)
    delete[] mat.elementi[i];
  delete[] mat.elementi;
  mat.elementi = nullptr;
}

template <typename TipElemenata>
Matrica<TipElemenata> StvoriMatricu(int br_redova, int br_kolona,
                                    char ime = 0) {
  Matrica<TipElemenata> mat;
  mat.br_redova = br_redova;
  mat.br_kolona = br_kolona;
  mat.ime_matrice = ime;
  mat.elementi = new TipElemenata *[br_redova] {};
  try {
    for (int i = 0; i < br_redova; i++)
      mat.elementi[i] = new TipElemenata[br_kolona];
  } catch (...) {
    UnistiMatricu(mat);
    throw;
  }
  return mat;
}

template <typename TipElemenata> void UnesiMatricu(Matrica<TipElemenata> &mat) {
  for (int i = 0; i < mat.br_redova; i++)
    for (int j = 0; j < mat.br_kolona; j++) {
      std::cout << mat.ime_matrice << "(" << i + 1 << "," << j + 1 << ") = ";
      std::cin >> mat.elementi[i][j];
    }
}

template <typename TipElemenata>
void IspisiMatricu(Matrica<TipElemenata> mat, int sirina_ispisa,
                   int preciznost = 6, bool treba_brisati = false) {
  for (int i = 0; i < mat.br_redova; i++) {
    for (int j = 0; j < mat.br_kolona; j++)
      std::cout << std::setprecision(preciznost) << std::setw(sirina_ispisa)
                << mat.elementi[i][j];
    std::cout << std::endl;
  }
  if (treba_brisati) {
    UnistiMatricu(mat);
  }
}

template <typename TipElemenata>
Matrica<TipElemenata> ZbirMatrica(const Matrica<TipElemenata> &m1,
                                  const Matrica<TipElemenata> &m2) {
  if (m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)
    throw std::domain_error("Matrice nemaju jednake dimenzije!");
  auto m3 = StvoriMatricu<TipElemenata>(m1.br_redova, m1.br_kolona);
  for (int i = 0; i < m1.br_redova; i++)
    for (int j = 0; j < m1.br_kolona; j++)
      m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
  return m3;
}

template <typename TipElemenata>
Matrica<TipElemenata> ProduktMatrica(const Matrica<TipElemenata> &m1,
                                     const Matrica<TipElemenata> &m2) {
  if (m1.br_kolona != m2.br_redova)
    throw std::domain_error("Matrice nisu saglasne za mnozenje!");

  auto m3 = StvoriMatricu<TipElemenata>(m1.br_redova, m2.br_kolona);
  for (int i = 0; i < m1.br_redova; i++) {
    for (int j = 0; j < m2.br_kolona; j++) {
      TipElemenata suma = TipElemenata();
      for (int k = 0; k < m1.br_kolona; k++)
        suma += m1.elementi[i][k] * m2.elementi[k][j];
      m3.elementi[i][j] = suma;
    }
  }
  return m3;
}
template <typename TipElemenata>
Matrica<TipElemenata> MatricniHarmonijskiPolinom(const Matrica<TipElemenata> &m,
                                                 int n) {
  if (m.br_kolona != m.br_redova)
    throw std::domain_error("Matrica nije kvadratna");
  if (n < 0)
    throw std::domain_error("Pogresan parametar n");

  auto rez = StvoriMatricu<TipElemenata>(m.br_redova, m.br_kolona);

  try {
    for (int i = 0; i < m.br_redova; i++)
      for (int j = 0; j < m.br_kolona; j++)
        rez.elementi[i][j] = TipElemenata();

    if (n == 0)
      return rez;

    auto stepen = StvoriMatricu<TipElemenata>(m.br_redova, m.br_kolona);

    for (int i = 0; i < m.br_redova; i++)
      for (int j = 0; j < m.br_kolona; j++)
        stepen.elementi[i][j] = m.elementi[i][j];

    for (int k = 1; k <= n; k++) {
      for (int i = 0; i < m.br_redova; i++)
        for (int j = 0; j < m.br_kolona; j++)
          rez.elementi[i][j] += stepen.elementi[i][j] / static_cast<double>(k);

      if (k != n) {
        auto novi_stepen = ProduktMatrica(stepen, m);
        UnistiMatricu(stepen);
        stepen = novi_stepen;
      }
    }
    UnistiMatricu(stepen);
    return rez;

  } catch (...) {
    UnistiMatricu(rez);
    throw;
  }
}

int main() {
  Matrica<double> a;
  int dimenzija;
  std::cout << "Unesite dimenziju kvadratne matrice: ";
  std::cin >> dimenzija;
  try {
    a = StvoriMatricu<double>(dimenzija, dimenzija, 'A');
    std::cout << "Unesite elemente matrice A: \n";
    UnesiMatricu(a);
    int n;
    std::cout << "Unesite red polinoma: ";
    std::cin >> n;

    auto H = MatricniHarmonijskiPolinom(a, n);

    std::cout << "Matricni harmonijski polinom: \n";
    IspisiMatricu(H, 10, 6);
    UnistiMatricu(H);
  } catch (std::bad_alloc &) {
    std::cout << "Nema dovoljno memorije!\n";
  } catch (std::exception &e) {
    std::cout << e.what() << "\n";
  }
  UnistiMatricu(a);

  return 0;
}
