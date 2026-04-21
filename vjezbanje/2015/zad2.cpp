#include <iostream>
#include <vector>

void OdstraniBrojeveSaIstomParnosti(std::vector<int> &v) {
  for (int i = 0; i < v.size(); i++) {
    int temp = v.at(i);
    bool cifra_izbacena = false;

    if (temp >= 10) {
      int cifra1 = temp % 10;
      temp /= 10;

      while (temp > 0) {
        int cifra2 = temp % 10;

        if (cifra2 % 2 == cifra1 % 2) {
          cifra_izbacena = true;
          break;
        }
        cifra1 = cifra2;
        temp /= 10;
      }
    }
    if (cifra_izbacena) {
      for (int j = i; j < v.size() - 1; j++)
        v.at(j) = v.at(j + 1);
      v.pop_back();
      i--;
    }
  }
}

int main() {
  int n;
  std::cout << "Unesite n: ";
  std::cin >> n;

  std::vector<int> slijed(n);
  for (auto &x : slijed) {
    std::cin >> x;
  }
  OdstraniBrojeveSaIstomParnosti(slijed);
  std::cout << "Rezultat: \n";
  for (auto &x : slijed) {
    std::cout << x << " ";
  }
  std::cout << "\n";
  return 0;
}