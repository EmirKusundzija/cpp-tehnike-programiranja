#include <iostream>
bool UnosDatuma(int &dan, int &mjesec, int &godina) {
  std::cout << "Unesite dan, mjesec i godinu: ";
  std::cin >> dan >> mjesec >> godina;

  if ((mjesec < 1 || mjesec > 12) || (godina < 2000 || godina > 2099))
    return false;
  return true;
}

int main() {
  for (;;) {
    int d, m, g;
    bool test = UnosDatuma(d, m, g);
    if (test) {
      std::cout << d << "/" << m << "/" << g << "\n";
      break;
    }
    std::cout << "DATUM JE NEISPRAVAN!\n";
  }
  return 0;
}