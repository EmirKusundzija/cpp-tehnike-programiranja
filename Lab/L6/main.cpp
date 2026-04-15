#include <iostream>
#include <new>
#include <stdexcept>
#include <vector>
int **MatricaIzVektora(std::vector<int> &v1, std::vector<int> &v2) {
  if (v1.empty() || v2.empty())
    throw std::logic_error("Vektori v1 i v2 ne smiju biti prazni");

  int redovi = v1.size();
  int kolone = v2.size();

  int **mat = new int *[redovi]();

  try {
    for (int i = 0; i < redovi; i++) {
      mat[i] = new int[kolone];
      for (int j = 0; j < kolone; j++) {
        bool i_parno = (v1.at(i) % 2 == 0);
        bool j_parno = (v2.at(j) % 2 == 0);

        if (i_parno && j_parno) {
          mat[i][j] = v1.at(i) + v2.at(j);
        } else if (!i_parno && !j_parno) {
          mat[i][j] = v1.at(i) - v2.at(j);
        } else
          mat[i][j] = v1.at(i) * v2.at(j);
      }
    }
  } catch (std::bad_alloc &) {
    for (int i = 0; i < redovi; i++) {
      delete[] mat[i];
    }
    delete[] mat;
    throw;
  }

  return mat;
}

int main() {

  int elementi_1;
  std::cout << "Unesite broj elemenata prvog vektora: ";
  std::cin >> elementi_1;

  std::vector<int> vec1(elementi_1);

  for (auto &x : vec1)
    std::cin >> x;

  int elementi_2;
  std::cout << "Unesite broj elemenata drugog vektora: ";
  std::cin >> elementi_2;

  std::vector<int> vec2(elementi_2);

  for (auto &x : vec2)
    std::cin >> x;

  int **matrica = nullptr;

  try {
    matrica = MatricaIzVektora(vec1, vec2);

    std::cout << "Rezultat: \n";
    for (int i = 0; i < elementi_1; i++) {
      for (int j = 0; j < elementi_2; j++) {
        std::cout << matrica[i][j] << " ";
      }
      std::cout << "\n";
    }

    for (int i = 0; i < elementi_1; i++) {
      delete[] matrica[i];
    }
    delete[] matrica;
  } catch (std::logic_error &e) {
    std::cout << "GRESKA: " << e.what() << "!\n";
  } catch (std::bad_alloc &) {
    std::cout << "Nedovoljno memorije!\n";
  }

  return 0;
}