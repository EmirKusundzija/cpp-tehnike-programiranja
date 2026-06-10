#include <iostream>

class NeobicnaKlasa {
public:
  explicit NeobicnaKlasa(int broj) { std::cout << "Direktna inicijalizacija"; }
  NeobicnaKlasa(double broj) { std::cout << "Kopirajuca inicijalizacija"; }
};

int main() {
  NeobicnaKlasa k1(5);
  NeobicnaKlasa k2 = 5;
  return 0;
}
