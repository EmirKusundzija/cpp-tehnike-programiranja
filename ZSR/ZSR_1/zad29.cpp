#include <iostream>

int main() {
  int a, b;

  std::cout << "Unesite a i b: ";
  std::cin >> a >> b;
  int br = 0;

  for (int i = a; i <= b; i++) {

    int temp = i;
    int suma = 0;
    while (temp > 0) {

      int cifra = temp % 10;
      suma += cifra;
      temp /= 10;
    }
    if (i % suma == 0)
      br++;
  }
  std::cout << "Rez: " << br;
}