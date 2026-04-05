
#include <iostream>
#include <stdexcept>
#include <vector>

int BrojCifara(long long n) {
  int temp = n;
  int br = 0;
  while (temp > 0) {
    int cifra = temp % 10;
    temp /= 10;
    br++;
  }
  return br;
}

std::vector<int> BrojCifaraUVektoru(std::vector<long long int> v) {

  std::vector<int> rez;
  for (int i = 0; i < v.size(); i++) {
    if (v.at(i) < 0)
      throw std::domain_error("Element je negativan, ne budite debili!");
    rez.push_back(BrojCifara(v.at(i)));
  }
  return rez;
}

int main() {
  try {
    std::vector<long long int> testiranje{1,   3,    15,     6,    516,
                                          899, 2421, 654645, 8484, 52};
    std::vector<int> fun(BrojCifaraUVektoru(testiranje));
    for (auto x : fun) {
      std::cout << x << "\n";
    }
  } catch (std::domain_error &e) {
    std::cout << "Greska: " << e.what() << "\n";
  }

  return 0;
}