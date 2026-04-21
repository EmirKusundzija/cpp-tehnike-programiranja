#include <cstdlib>
#include <iostream>
#include <stdexcept>

int **AlocirajFragmentirano(int n) {
  if (n <= 0)
    throw std::domain_error("Pogresan parametar");
  int **mat = nullptr;

  try {
    mat = new int *[n] {};

    for (int i = 0; i < n; i++)
      mat[i] = new int[2 * i + 1]; // idemo od n n-1 n-2 ... n-2 n-1 n
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < 2 * i + 1; j++) {
        mat[i][j] = std::abs(i - j) + 1;
      }
    }
  } catch (...) {
    for (int i = 0; i < n; i++) {
      delete[] mat[i];
    }
    delete[] mat;
    std::cout << "Kreiranje nije uspjelo";
  }

  return mat;
}

int **AlocirajKontinualno(int n) {
  if (n <= 0)
    throw std::domain_error("Pogresan parametar");
  int **mat = nullptr;

  try {
    mat = new int *[n] {};
    mat[0] = new int[2 * n + 1];
    for (int i = 1; i < n; i++)
      mat[i] = mat[i - 1] + (2 * (i - 1) + 1);

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < 2 * i + 1; j++) {
        mat[i][j] = std::abs(i - j) + 1;
      }
    }
  } catch (...) {
    delete[] mat[0];
    delete[] mat;
    std::cout << "Kreiranje nije uspjelo";
  }

  return mat;
}

int main() {
  try {
    int n;
    std::cout << "Unesite broj redova: ";
    std::cin >> n;

    int **mat = AlocirajFragmentirano(n);

    std::cout << "Rezultat: \n";
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < 2 * i + 1; j++) {
        std::cout << mat[i][j] << " ";
      }
      std::cout << "\n";
    }
    for (int i = 0; i < n; i++) {
      delete[] mat[i];
    }
    delete[] mat;

    int m;
    std::cout << "Unesite broj redova (ponovo jbga): ";
    std::cin >> m;

    int **mat2 = AlocirajKontinualno(m);
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < 2 * i + 1; j++) {
        std::cout << mat2[i][j] << " ";
      }
      std::cout << "\n";
    }
    delete[] mat2[0];
    delete[] mat2;

  } catch (std::domain_error &e) {
    std::cout << e.what() << "!\n";
  }
}