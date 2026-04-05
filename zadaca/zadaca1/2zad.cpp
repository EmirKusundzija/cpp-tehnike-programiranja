// TP 2025/2026: Zadaća 1, Zadatak 2
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>
typedef std::vector<std::vector<double>> Matrica;

std::vector<double> SelectionSort(std::vector<double> v) {

  for (int i = 0; i < v.size(); i++) {
    int min = i;
    for (int j = i + 1; j < v.size(); j++) {
      if (v.at(j) < v.at(min))
        min = j;
    }
    double temp = v.at(i);
    v.at(i) = v.at(min);
    v.at(min) = temp;
  }

  return v;
}

double Medijan(std::vector<double> v) {
  v = SelectionSort(v);
  if (v.size() % 2 != 0)
    return v.at(v.size() / 2);
  else
    return (v.at(v.size() / 2 - 1) + v.at(v.size() / 2)) / 2.0;
}

Matrica KreirajMatricu(int br_redova, int br_kolona) {
  return Matrica(br_redova, std::vector<double>(br_kolona));
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

void IspisiMatricu(Matrica m) {
  for (int i = 0; i < m.size(); i++) {
    for (int j = 0; j < m.at(i).size(); j++) {
      std::cout << std::fixed << std::setprecision(2) << std::setw(7)
                << m.at(i).at(j);
    }
    std::cout << "\n";
  }
}

Matrica MedijanskiFilter(Matrica m, int N) {
  if (N < 0)
    throw std::domain_error("Neispravan red filtriranja");

  Matrica rezultat = m;

  for (int i = 0; i < m.size(); i++) {
    for (int j = 0; j < m.at(i).size(); j++) {
      std::vector<double> prozor;
      for (int ni = i - N; ni <= i + N; ni++) {
        for (int nj = j - N; nj <= j + N; nj++) {
          if (ni >= 0 && ni < m.size() && nj >= 0 && nj < m.at(ni).size())
            prozor.push_back(m.at(ni).at(nj));
        }
      }
      rezultat.at(i).at(j) = Medijan(prozor);
    }
  }

  return rezultat;
}

int main() {
  try {
    int red, kolona;
    std::cout << "Unesite broj redova i kolona matrice: ";
    std::cin >> red >> kolona;

    std::cout << "Unesite elemente matrice: ";
    Matrica A = UnesiMatricu(red, kolona);

    int N;
    std::cout << "Unesite red filtriranja: ";
    std::cin >> N;

    Matrica rez = MedijanskiFilter(A, N);

    std::cout << "\nMatrica nakon filtriranja: \n";
    IspisiMatricu(rez);
  } catch (std::domain_error izuzetak) {
    std::cout << "\nGRESKA: " << izuzetak.what() << "!\n";
  }

  return 0;
}
