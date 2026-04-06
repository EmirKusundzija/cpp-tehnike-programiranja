#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>

typedef std::vector<std::vector<double>> Matrica;

Matrica KreirajMatricu(int br_redova, int br_kolona) {
  return Matrica(br_redova, std::vector<double>(br_kolona));
}

Matrica UnesiMatricu(int br_redova) {
  auto m = KreirajMatricu(br_redova, 0);
  for (int i = 0; i < br_redova; i++) {
    int n_elementi;
    std::cout << "Unesite br. elemenata: ";
    std::cin >> n_elementi;
    for (int j = 0; j < n_elementi; j++) {
      std::cout << "Element na poziciji (" << i + 1 << "," << j + 1 << "): ";
      std::cin >> m[i][j];
    }
  }
  return m;
}

int BrojRedova(Matrica m) { return m.size(); }

int BrojKolona(Matrica m) { return m.size() != 0 ? m.at(0).size() : 0; }

Matrica ProizvodMatrica(Matrica a, Matrica b) {
  auto c = KreirajMatricu(BrojRedova(a), BrojKolona(b));

  if (BrojRedova(b) != BrojKolona(a))
    throw std::domain_error("Matrice nisu saglasne za mnozenje!");
  if (BrojKolona(b) == 0 || BrojRedova(a) == 0)
    throw std::logic_error(
        "Gdje ste vidjeli da matrica [mxn] ima oblik mx0 ili 0xn!");

  for (int i = 0; i < BrojRedova(a); i++) {
    for (int j = 0; j < a[i].size(); j++) {
      double suma = 0.0;
      for (int k = 0; k < b[j].size(); k++)
        suma += a[i][k] * b[k][j];
      c[i][j] = suma;
    }
  }

  return c;
}

void IspisiMatricu(Matrica m) {
  for (int i = 0; i < BrojRedova(m); i++) {
    for (int j = 0; j < BrojKolona(m); j++) {
      std::cout << std::setw(10) << std::fixed << std::setprecision(3)
                << m[i][j] << " ";
    }
    std::cout << "\n";
  }
}

int main() {
  try {
    int red_A, kolona_A;
    std::cout << "Unesite redove i kolone A: ";
    std::cin >> red_A;
    Matrica A = UnesiMatricu(red_A);
    int red_B;
    std::cout << "Unesite redove i kolone B: ";
    std::cin >> red_B;
    Matrica B = UnesiMatricu(red_B);
    std::cout << "\n";

    Matrica C = ProizvodMatrica(A, B);

    IspisiMatricu(C);
  } catch (std::domain_error e) {
    std::cout << "Izuzetak: " << e.what() << "\n";
  } catch (std::logic_error e) {
    std::cout << "Hall of shame: " << e.what() << "\n";
  }

  return 0;
}