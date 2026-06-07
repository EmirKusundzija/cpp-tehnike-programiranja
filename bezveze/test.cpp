#include <algorithm>
#include <functional>
#include <iostream>

int main() {
  // ispravno
  int n;

  std::cout << "Unesite n brojeva: ";
  std::cin >> n;
  try {
    int *a = new int[n];
    for (int i = 0; i < n; i++) {
      std::cin >> a[i];
    }
    std::sort(a, a + n, std::greater<int>());
    for (int i = 0; i < n; i++) {
      std::cout << a[i] << " ";
    }
    delete[] a;
  } catch (...) {

    std::cout << "Problemi sa memorijom";
  }

  // neispravno (UB)
  // int x=3;
  // int b[x];

  return 0;
}
