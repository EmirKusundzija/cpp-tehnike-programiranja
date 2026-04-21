#include <iostream>
#include <stdexcept>

int **PascalovTrougao(int n) {
  int **mat = nullptr;
  if (n <= 0)
    throw std::domain_error("Pogresan parametar!");
  try {
    mat = new int *[n];
    mat[0] = new int[n * (n + 1) / 2];

    for (int i = 1; i < n; i++)
      mat[i] = mat[i - 1] + i;

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < i + 1; j++) {
        if (j == 0 || j == i)
          mat[i][j] = 1;
        else
          mat[i][j] = mat[i - 1][j - 1] + mat[i - 1][j];
      }
    }
  } catch (...) {
    delete[] mat[0];
    delete[] mat;
    std::cout << "Kreiranje nije uspjelo!\n";
  }
  return mat;
}

int main() {

  try {
    int n;
    std::cout << "Unesite n: ";
    std::cin >> n;

    int **mat = PascalovTrougao(n);

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < i + 1; j++) {
        std::cout << mat[i][j] << " ";
      }
      std::cout << "\n";
    }
    delete[] mat[0];
    delete[] mat;
  } catch (std::domain_error &e) {
    std::cout << e.what() << " ";
  }

  return 0;
}